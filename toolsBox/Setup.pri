BASEDIR_WIN = $$replace(PWD, "/", "\\")
DESTDIR_WIN = $$replace(DESTDIR, "/", "\\")
QT_BIN_DIR  = $$dirname(QMAKE_QMAKE)

QMAKE_POST_LINK += $$escape_expand(\\n)  $$QMAKE_COPY_DIR \"$$BASEDIR_WIN\\pack\" \"$$DESTDIR_WIN\\pack\"
QMAKE_POST_LINK += $$escape_expand(\\n)  $$QMAKE_COPY \"$$DESTDIR_WIN\\libs\\*.dll\" \"$$DESTDIR_WIN\"

# 拷贝必要文件
ReleaseBuild {
    # Copy Visual Studio DLLs
    # Note that this is only done for release because the debugging versions of these DLLs cannot be redistributed.
    win32-msvc2010 {
        QMAKE_POST_LINK += $$escape_expand(\\n) $$QMAKE_COPY \"C:\\Windows\\System32\\msvcp100.dll\"  \"$$DESTDIR_WIN\"
        QMAKE_POST_LINK += $$escape_expand(\\n) $$QMAKE_COPY \"C:\\Windows\\System32\\msvcr100.dll\"  \"$$DESTDIR_WIN\"
    }
    else:win32-msvc2012 {
        QMAKE_POST_LINK += $$escape_expand(\\n) $$QMAKE_COPY \"C:\\Windows\\System32\\msvcp110.dll\"  \"$$DESTDIR_WIN\"
        QMAKE_POST_LINK += $$escape_expand(\\n) $$QMAKE_COPY \"C:\\Windows\\System32\\msvcr110.dll\"  \"$$DESTDIR_WIN\"
    }
    else:win32-msvc2013 {
        QMAKE_POST_LINK += $$escape_expand(\\n) $$QMAKE_COPY \"C:\\Windows\\System32\\msvcp120.dll\"  \"$$DESTDIR_WIN\"
        QMAKE_POST_LINK += $$escape_expand(\\n) $$QMAKE_COPY \"C:\\Windows\\System32\\msvcr120.dll\"  \"$$DESTDIR_WIN\"
    }
    else:win32-msvc2015 {
        QMAKE_POST_LINK += $$escape_expand(\\n) $$QMAKE_COPY \"C:\\Windows\\System32\\msvcp140.dll\"  \"$$DESTDIR_WIN\"
        QMAKE_POST_LINK += $$escape_expand(\\n) $$QMAKE_COPY \"C:\\Windows\\System32\\vcruntime140.dll\"  \"$$DESTDIR_WIN\"
    }
    else {
        error("Visual studio version not supported, installation cannot be completed.")
    }
}
