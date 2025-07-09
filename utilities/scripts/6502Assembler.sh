#!/bin/bash

romSize=32768

libraryFilePath="libraries/rommanager/rommanager.h"

filePrefix="UnixCore-6502"

jsonFileName="$filePrefix.json"
assemblyFileName="$filePrefix.s"
binaryFileName="$filePrefix.out"

if [ ! -e "$1" ] || [[ ! "$1" =~ UnixCore-6502\.s$ ]]; then

    echo "Warning: the provided path is invalid. The current directory will be used instead." >&2
    echo "Looking for the '$assemblyFileName' in the current directory."

    if ! ls "$assemblyFileName" 1>/dev/null 2>&1; then

        echo "Error: no '$assemblyFileName' file found in the current directory." >&2
        exit 1
    
    fi
    
    filePath="$assemblyFileName"

else

    filePath="$1"

fi

vasm=$(vasm -Fbin -dotdir "$filePath" -o "$binaryFileName")

seg8000=$(echo "$vasm" | awk '/seg8000/ {print $2}')
segfffc=$(echo "$vasm" | awk '/segfffc/ {print $2}')

if [ -n "$seg8000" ] && [ $seg8000 -gt 0 ] && [ $seg8000 -le $(($romSize - 6)) ]; then

    hexdump=$(hexdump -v -e '1/1 "0x%02x "' "$binaryFileName")
    
    rm "$binaryFileName"

    hexCode=$(echo $hexdump | cut -d ' ' -f1-$seg8000 | xargs -n 17)

    if [ -z "$segfffc" ] || [ $segfffc -lt 2 ]; then

        echo "Error: 'segfffc' field not found or smaller than 2 bytes." >&2
        exit 1
    
    fi

    fffc=$(echo $hexdump | cut -d ' ' -f$((${romSize} - 3)))
    fffd=$(echo $hexdump | cut -d ' ' -f$((${romSize} - 2)))

    if [ "$fffc" != "0x00" ] || [ "$fffd" != "0x80" ]; then

        echo 'Error: the program must start at address $8000.' >&2
        exit 1
    
    fi

    if [ $segfffc -eq 4 ]; then

        fffe=$(echo $hexdump | cut -d ' ' -f$((${romSize} - 1)))
        ffff=$(echo $hexdump | cut -d ' ' -f${romSize})

    fi

    fffe=${fffe:-0x00}
    ffff=${ffff:-0x00}

    sed -i "s/#define FFFE\s\+0x[0-9A-Fa-f][0-9A-Fa-f]/#define FFFE ${fffe}/" ../../${libraryFilePath}
    sed -i "s/#define FFFF\s\+0x[0-9A-Fa-f][0-9A-Fa-f]/#define FFFF ${ffff}/" ../../${libraryFilePath}

    echo "The 'code' array in the file '$jsonFileName' will be cleared."

    temporaryJsonData=$(jq '.code = []' ../../$jsonFileName)

    for ((row = 1; row <= $(echo "$hexCode" | wc -l); row++)); do

        temporaryJsonData=$(echo "$temporaryJsonData" | jq --arg hexRow "$(echo "$hexCode" | sed -n "$row p")" '.code['$(( $row - 1 ))'] = $hexRow')

    done

    authorFullName="$(git config --global user.name)"

    if [ -n "$authorFullName" ]; then

        temporaryJsonData=$(echo "$temporaryJsonData" | jq --arg author "$authorFullName" '.author = $author')

    else

        echo "Error: you must set your user name for Git. Use 'git config --global user.name "Name Surname"' to configure it." >&2
        exit 1

    fi

    echo "$temporaryJsonData" | jq > ../../$jsonFileName
    echo "Data successfully stored in the '$jsonFileName' json file!"
    exit 0

fi

[ -e "$binaryFileName" ] && rm "$binaryFileName"

echo "Error: 'seg8000' field not found, empty (zero bytes) or exceeds the allowed size." >&2
exit 1