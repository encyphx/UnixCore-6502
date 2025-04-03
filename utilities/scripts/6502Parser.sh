#!/bin/bash

# Please, ensure jq is installed for the script to operate.

if ! command -v jq > /dev/null; then
    echo "Error: please, ensure jq is installed for the script to operate." >&2
    exit 1
fi

libraryFilePath="libraries/rommanager/rommanager.h"
jsonFileName="UnixCore-6502.json"
maxSIZE=16384
modifiedFile=$(git diff --name-only ../../${jsonFileName})

if ! jq empty ../../$jsonFileName 2> /dev/null; then

    echo "Error: The JSON file '$jsonFileName' is invalid. Please check the structure and try again!" >&2
    exit 1

fi

if [ -z "$modifiedFile" ]; then

    echo "Error: the '$jsonFileName' file has not been modified!" >&2
    exit 1

fi

if invalidEntries=$(jq -r '.code[]' ../../$jsonFileName | grep -Pv '^(0x[0-9a-fA-F]{2}( 0x[0-9a-fA-F]{2}){0,16})$'); then

    echo "Error: invalid lines detected in '${jsonFileName}'. These lines need to be reviewed and fixed:" >&2
    echo "$invalidEntries" >&2
    exit 1

fi

SIZE=$(jq -r '.code | join(" ")' ../../$jsonFileName | wc -w)

if [ $SIZE -le $maxSIZE ]; then

    arrayElements=$(jq -r '.code | join(" ") | split(" ") | join(", ") | "{" + . + "}"' ../../$jsonFileName)
    sed -i "s/#define HEXCODE\s\+{[^}]*}/#define HEXCODE ${arrayElements}/" ../../${libraryFilePath}
    sed -i "s/#define SIZE\s\+[0-9]\+/#define SIZE ${SIZE}/" ../../${libraryFilePath}
    echo "Done."
    exit 0

fi

echo "Error: you have exceeded the allowed size!" >&2
exit 1
