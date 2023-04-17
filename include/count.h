//
// Created by sid on 4/14/23.
//

#ifndef COUNT_COUNT_H
#define COUNT_COUNT_H

int count_files(const char* dir_path, int include_hidden);
int count_files_and_folders(const char* dir_path, int include_hidden);
int count_files_and_links(const char* dir_path, int include_hidden);
int count_items(const char* dir_path, int include_hidden);
int count_query(const char* dir_path, int include_hidden, int include_files, int include_dirs, int include_links);

#endif //COUNT_COUNT_H
