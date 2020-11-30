/*
wjz
*/
#include "rmdir.h"
#include "Shell.h"

int exec_rmdir(char *cmd){
    char* args = split_blank(cmd, 1);
    char* token = split_blank(cmd, 1);
    char* input_yn = (char*)malloc(4);
    if (args == NULL) {
        puts("None arguments for rmdir! Please check your input!");
        return 1;
    }
    if (token == NULL) {
        while (1) {
            printf("If you want to remove the directory: %s? Please input [yes/no] ", args);
            ssize_t buffer;
            size_t buf_bytes = 4;
            buffer = getline(&input_yn, &buf_bytes, stdin);
            input_yn[(int)--buffer] = '\0';
            if (strcmp(input_yn, "no") == 0 || strcmp(input_yn, "yes") == 0) {
                break;
            }
            else {
                puts("Your input is wrong! Please check and re_input!");
            }
        }
        if (strcmp(input_yn, "yes") == 0) {
            myrmdir(args);

        }
    }
    else {
        if (strcmp(args, "-p") == 0) {
            int tag;
            int tag1;//记录删除成功的信息
            char* sonpath;//子目录
            char path_now[100];//记忆while循环里的目录
            char* pathnow[100];//记住当前目录，然后在while里和getcwd对比是否到了当前目录，到了就说明删完了
            //char* process_path;//用于记录删目录过程中的当前目录。
            char* token1;//token的复制品，因为直接调用dirname(token)会改变token,而basename()不会！！！可以直接名为fatherpath，需要精简。
            char* fatherpath="NULL";//父目录
            token1 = malloc(4);//！！！！分配内存空间，不然会出现段错误
            strcpy(token1, token);
            getcwd(pathnow, sizeof(pathnow));//把当前目录传到pathnow里面  编译出警告！！！！！！！因为path_now
            fatherpath = dirname(token1);//dirname命令去除文件名中的非目录部分，删除最后一个“\”后面的路径，显示父目录。 //token1没问题，fatherpath没问题
            sonpath = basename(token);//basename命令用于打印目录或者文件的基本名称，显示最后的目录名或文件名。
            tag = chdir(fatherpath);//段错误之源,fatherpath导致的段错误！！！！！！
            if (tag == -1) {
                printf("Wrong path! Directory: %s does not exist\n", fatherpath);//tag 自动成为-1.而且出现了段错误
            }
            
            else {
                
                tag1=myrmdir(sonpath);
                if (tag1=1){
                    while (strcmp(fatherpath, pathnow) < 0 || strcmp(fatherpath, pathnow) > 0) {
                        getcwd(path_now, sizeof(path_now));
                        sonpath = basename(path_now);
                        fatherpath = dirname(path_now);
                        chdir(fatherpath);
                        getcwd(path_now, sizeof(path_now));
                        fatherpath = path_now;
                        DIR* fd;
                        int ret;
                        fd = opendir(sonpath);//如果path是个文件返回NULL ,检查是文件还是文件夹
                        if (fd == NULL)
                        {
                            printf("error,it is a file,or it is not exist -- %s\n", sonpath);
                            break;//删除一个失败后就全部失败了
                        }
                        closedir(fd);

                        ret = rmdir(sonpath);
                        if (ret == -1)
                        {
                            printf("filed to delete it-%s\n", sonpath);
                            break;
                        }
                        else
                            printf("rm dir: %s\n", sonpath);


                    }
                }
                
                
            }
            
            free(token1);
        }
        
        else {
            char* token_new;
            if (args != NULL) {
                myrmdir(args);
            }
            if (token != NULL) {
                myrmdir(token);
            }
            while (token_new = split_blank(cmd, 1)) {
                myrmdir(token_new);
                }
        }
        free(input_yn);
        return 1;
    }
}
int myrmdir(char* a) {
    DIR* fd;
    int ret;
    fd = opendir(a);//如果path是个文件返回NULL ,检查是文件还是文件夹
    if (fd == NULL)
    {
        printf("error,it is a file,or it is not exist -- %s\n", a);
    }
    closedir(fd);

    ret = rmdir(a);
    if (ret == -1)
    {
        printf("filed to delete it-%s\n", a);
        return 0;
    }
    else {
        printf("rm dir: %s\n", a);
        return 1;
    }
}