
#ifndef GET_SYSCONST_H
#define GET_SYSCONST_H

#define S_ISFIFO(_M) ((_M & _S_IFMT)==_S_IFIFO)
#define S_ISDIR(_M)  ((_M & _S_IFMT)==_S_IFDIR)

#define ZIP_COMMAND 		"%TC_ROOT%\\bin\\zip -R"
#define MOVE_COMMAND 		"MOVE /Y"
#define REMOVE_DIR 			"RMDIR /S /Q"
#define FILE_SEP_WIN32 		"\\"
#define PATH_SEP_WIN32 		";"
#define FILE_DEL_COMMAND 	"DEL /Q"
#define FILE_OPEN_COMMAND   "type"
#define PLOT_TEMP_DIR       "C:\\TEMP"
#define POPEN				_popen
#define	PCLOSE				_pclose
#define ISUGCLONEAVAILABLE  true

#define WIN32_SLEEP		"anything_goes_here"

#endif /* GET_SYSCONST_H */
