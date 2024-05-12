count -- count the files in a directory 
![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/Sid220/count/cmake-multi-platform.yml)
=============================================

## SYNOPSIS

`count` `[--dir]` `[--hidden]` `[--link]` `[--output=FILE]` `[DIR...]`

## DESCRIPTION

**count** counts the number of files in a directory, or directories. It can also be configured (see [OPTIONS][]) to include directories, symbolic links, and hidden files in that count. Additionally, a C library is provided, see count(3) for more information.

## OPTIONS

These options control what types of files are counted, and whether output is written to a file or standard output.

`-o  FILE`, `--output=FILE`:
  Output to the given file instead of standard output.

`-h`, `--hidden`:
  Include hidden files (that is, those beginning with ".") in the file count.

`-d`, `--dir`:
  Include directories in the file count (non-recursive). Does not include cwd (".") or parent directory ("..")

`-l`, `--link`:
  Include symbolic links in the file count.

Miscellaneous options:

`-?`, `--help`:
  Show a short help menu.

`--usage`:
  Show a quick summary of usage options.

`-V`, `--version`:
  Show count version and exit.

## EXAMPLES

Count the number of files and folders in the home directory, excluding hidden files and folders:

    $ count /home/$USER -d
    5
    $

Count the number of files, including hidden and linked ones, in /var/www/html, and output it to the file /home/$USER/count.txt:

    $ count /var/www/html -hl --output=/home/$USER/count.txt
    $ cat /home/$USER/count.txt
    12
    $

## NOTES

The current working directory ("."), and parent directory ("..") are not included in any counts. No counts are recursive.

## COPYRIGHT

Copyright © 2023 Sidney Trzepacz.  License MIT: The MIT License <https://opensource.org/license/mit>.
This is free software: you are free to change and redistribute it.  There is NO WARRANTY OF ANY KIND, to the extent permitted by law.

## SEE ALSO

ls(1), wc(1), find(1)
