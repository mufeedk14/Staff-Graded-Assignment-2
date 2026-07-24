#!/bin/bash

mkdir -p backup
touch errors.txt
touch report.txt

processed_files=0
duplicate_files=0
files_backedup=0

for file in submissions/*; do
    [ -f "$file" ] || continue
    ((processed_files++))

    filename=$(basename "$file")

    if [ -f "backup/$filename" ]; then
        ((duplicate_files++))
    else
        cp "$file" backup/ 2>>errors.txt
        ((files_backedup++))
    fi
done

echo "Processed Files: $processed_files" > report.txt
echo "Duplicate Files: $duplicate_files" >> report.txt
echo "Backed Up Files: $files_backedup" >> report.txt

#The script first creates the needed files and also ensures that the backup directory exists, it then iterates through every file in submissions directory and first checks if it is a file by [ -f "$file" ] command or else it skips this and continues to next file, it then increments the variable which holds the number of files processed.
#Then the basename of file is found using basename command and stored into filename variable then the if statements checks whether a file in backup has the same name or not, if it does it increments duplicate_files otherwise copies the file to the backup folder.
#In the end the number of files processed, duplicate files and files backedup is stored in report.txt
