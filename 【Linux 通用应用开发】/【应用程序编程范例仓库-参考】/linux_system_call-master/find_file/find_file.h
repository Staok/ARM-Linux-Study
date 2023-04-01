/*
 * =====================================================================================
 *
 *       Filename:  find_file.h
 *
 *    Description:  在目录中查找制定类型的文件
 *
 *        Version:  1.0
 *        Created:  2013年07月18日 16时15分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hurley (LiuHuan), liuhuan1992@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */

#ifndef FIND_FILE_H_
#define FIND_FILE_H_

// 待寻找类型的文件数量
extern int file_count;

// 对文件的处理函数
void process_file(char *filename, char *type);

// 递归遍历一个目录
void find_directory(char *dir_name, void (*process_file)(char *, char *), char *type);

// 打印使用方法
void print_useage(char *filename);

#endif  // FIND_FILE_H_

