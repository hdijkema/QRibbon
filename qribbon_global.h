#ifndef QRIBBON_GLOBAL_H
#define QRIBBON_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QRIBBON_LIBRARY)
#  define QRIBBON_EXPORT Q_DECL_EXPORT
#else
#  if defined(QRIBBON_TEST)
#    define QRIBBON_EXPORT
#  else
#    define QRIBBON_EXPORT Q_DECL_IMPORT
#  endif
#endif

#endif // QRIBBON_GLOBAL_H

