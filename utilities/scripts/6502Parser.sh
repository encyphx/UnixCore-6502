#!/bin/bash

libraryFilePath="libraries/rommanager/rommanager.h"
jsonFileName="UnixCore-6502.json"
maxSize=16384
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

hexSize=$(jq -r '.code | join(" ")' ../../$jsonFileName | wc -w)

if [ $hexSize -le $maxSize ]; then

    L_HEXCODE=$(jq -r '.code | join(" ") | split(" ") | join(", ") | "{" + . + "}"' ../../$jsonFileName)

    sed -ri "s/#define L_HEXCODE\s+\{(\s*0x[0-9A-Fa-f]{2}(\s*,\s*0x[0-9A-Fa-f]{2})*\s*)?\}/#define L_HEXCODE ${L_HEXCODE}/" ../../${libraryFilePath}
    sed -i "s/#define L_SIZE\s\+[0-9]\+/#define L_SIZE ${hexSize}/" ../../${libraryFilePath}

    sed -ri "s/#define H_HEXCODE\s+\{(\s*0x[0-9A-Fa-f]{2}(\s*,\s*0x[0-9A-Fa-f]{2})*\s*)?\}/#define H_HEXCODE {}/" ../../${libraryFilePath}
    sed -i "s/#define H_SIZE\s\+[0-9]\+/#define H_SIZE 0/" ../../${libraryFilePath}

else

    L_HEXCODE=$(jq -r '.code | join(" ") | split(" ")[0:'"${maxSize}"'] | join(", ") | "{" + . + "}"' ../../$jsonFileName)
    H_HEXCODE=$(jq -r '.code | join(" ") | split(" ")['"${maxSize}"':'"${hexSize}"'] | join(", ") | "{" + . + "}"' ../../$jsonFileName)

    sed -ri "s/#define L_HEXCODE\s+\{(\s*0x[0-9A-Fa-f]{2}(\s*,\s*0x[0-9A-Fa-f]{2})*\s*)?\}/#define L_HEXCODE ${L_HEXCODE}/" ../../${libraryFilePath}
    sed -i "s/#define L_SIZE\s\+[0-9]\+/#define L_SIZE ${maxSize}/" ../../${libraryFilePath}

    sed -ri "s/#define H_HEXCODE\s+\{(\s*0x[0-9A-Fa-f]{2}(\s*,\s*0x[0-9A-Fa-f]{2})*\s*)?\}/#define H_HEXCODE ${H_HEXCODE}/" ../../${libraryFilePath}
    sed -i "s/#define H_SIZE\s\+[0-9]\+/#define H_SIZE $((${hexSize} - ${maxSize}))/" ../../${libraryFilePath}

fi

echo "Done."
exit 0

