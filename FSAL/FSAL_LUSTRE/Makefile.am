AM_CFLAGS                     = $(FSAL_CFLAGS) $(SEC_CFLAGS)

if USE_FSAL_LUSTRE

if BUILD_SHARED_FSAL
lib_LTLIBRARIES = libfsallustre.la
libfsallustre_la_LDFLAGS = -version-number @LIBVERSION@
libfsallustre_la_LIBADD = ../../SemN/libSemN.la -llustreapi  ../libfsalcommon.la 
else
noinst_LTLIBRARIES          = libfsallustre.la
endif

libfsallustre_la_SOURCES = fsal_access.c      \
                          fsal_context.c     \
                          fsal_compat.c      \
                          fsal_dirs.c        \
                          fsal_fsinfo.c      \
                          fsal_rcp.c         \
                          fsal_truncate.c    \
			  fsal_attrs.c       \
                          fsal_convert.c     \
                          fsal_init.c        \
                          fsal_lookup.c      \
                          fsal_rename.c      \
                          fsal_symlinks.c    \
                          fsal_unlink.c      \
			  fsal_create.c      \
                          fsal_fileop.c      \
                          fsal_internal.c    \
                          fsal_stats.c       \
                          fsal_tools.c       \
                          fsal_xattrs.c      \
                          fsal_local_op.c    \
                          fsal_lock.c     \
			  fsal_internal.h    \
                          fsal_convert.h     \
                          ../../include/fsal.h       \
                          ../../include/fsal_types.h \
                          ../../include/err_fsal.h   \
                          ../../include/FSAL/FSAL_LUSTRE/fsal_types.h

if USE_FSALMDS
libfsallustre_la_SOURCES += fsal_mds.c        \
                            fsal_pnfs_tools.c
endif

if USE_FSALDS
libfsallustre_la_SOURCES += fsal_ds.c 
endif

endif

if USE_FSAL_SHOOK

if BUILD_SHARED_FSAL
lib_LTLIBRARIES = libfsalshook.la
libfsalshook_la_LDFLAGS = -version-number @LIBVERSION@
libfsalshook_la_LIBADD = ../../SemN/libSemN.la -llustreapi  ../libfsalcommon.la 
else
noinst_LTLIBRARIES          = libfsalshook.la
endif

libfsalshook_la_SOURCES = fsal_access.c      \
                          fsal_context.c     \
                          fsal_compat.c      \
                          fsal_dirs.c        \
                          fsal_fsinfo.c      \
                          fsal_rcp.c         \
                          fsal_truncate.c    \
                          fsal_attrs.c       \
                          fsal_convert.c     \
                          fsal_init.c        \
                          fsal_lookup.c      \
                          fsal_rename.c      \
                          fsal_symlinks.c    \
                          fsal_unlink.c      \
			  fsal_create.c      \
                          fsal_fileop.c      \
                          fsal_internal.c    \
                          fsal_stats.c       \
                          fsal_tools.c       \
                          fsal_xattrs.c      \
                          fsal_local_op.c    \
                          fsal_lock.c     \
			  fsal_internal.h    \
                          fsal_convert.h     \
                          ../../include/fsal.h       \
                          ../../include/fsal_types.h \
                          ../../include/err_fsal.h   \
                          ../../include/FSAL/FSAL_LUSTRE/fsal_types.h

if USE_FSALMDS
libfsalshook_la_SOURCES += fsal_mds.c
endif

if USE_FSALDS
libfsalshook_la_SOURCES += fsal_ds.c
endif


endif


new: clean all


