#include "ptyqt.h"
#include <utility>

#ifdef Q_OS_WIN
#include "winptyprocess.h"
#include "conptyprocess.h"
#endif

#ifdef Q_OS_UNIX
#include "unixptyprocess.h"
#endif

IPtyProcess *PtyQt::createPtyProcess(IPtyProcess::PtyType ptyType)
{
    switch (ptyType)
    {
#ifdef Q_OS_WIN
    case IPtyProcess::PtyType::WinPty:
        return new WinPtyProcess();
        break;
    case IPtyProcess::PtyType::ConPty:
        return new ConPtyProcess();
        break;
#endif
#ifdef Q_OS_UNIX
    case IPtyProcess::PtyType::UnixPty:
        return new UnixPtyProcess();
        break;
#endif
    case IPtyProcess::PtyType::AutoPty:
    default:
        break;
    }

#ifdef Q_OS_WIN
    if (ConPtyProcess().isAvailable())
        return new ConPtyProcess();
    else
        return new WinPtyProcess();
#endif
#ifdef Q_OS_UNIX
    return new UnixPtyProcess();
#endif
}
