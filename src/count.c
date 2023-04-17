#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int count_query(const char *dir_path, int include_hidden, int include_files, int include_dirs, int include_links) {
    int file_count = 0;
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        // handle error opening directory
        return -1;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' && !include_hidden) {
            continue; // skip hidden files
        }

        // Stop the pesky '..' parent directory, and '.' cwd
        // TODO: more efficient method
        if(include_dirs) {
            if(strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".") == 0) {
                continue;
            }
        }
        if ((include_dirs && entry->d_type == DT_DIR) || (include_files && entry->d_type == DT_REG) ||
            (include_links && entry->d_type == DT_LNK))
            // if the entry is a known file && type is correct, increment file_count
            file_count++;
    }
    closedir(dir);
    return file_count;
}

int count_files(const char *dir_path, int include_hidden) {
    return count_query(dir_path, include_hidden, 1, 0, 0);
}

int count_files_and_folders(const char *dir_path, int include_hidden) {
    return count_query(dir_path, include_hidden, 1, 1, 0);
}

int count_files_and_links(const char *dir_path, int include_hidden) {
    return count_query(dir_path, include_hidden, 1, 0, 1);
}

int count_items(const char *dir_path, int include_hidden) {
    return count_query(dir_path, include_hidden, 1, 1, 1);
}
