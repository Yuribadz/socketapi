/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2018  yuribadz <email>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "AppLogger.hpp"
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
#include "Poco/PatternFormatter.h"
#include "Poco/FormattingChannel.h"
#include "Poco/ConsoleChannel.h"
#include "Poco/FileChannel.h"
#include "Poco/Message.h"
#include <iostream>


using Poco::Logger;
using Poco::AutoPtr;
using Poco::PatternFormatter;
using Poco::FormattingChannel;
using Poco::ConsoleChannel;
using Poco::FileChannel;
using Poco::Message;

namespace applog {

Logger& setUp()
{
    AutoPtr<PatternFormatter> pPatternFormatter2(new PatternFormatter("%Y-%m-%d %H:%M:%S.%c %N[%P]:%s:%q: %t %U:%u"));
    AutoPtr<FormattingChannel> pFCFile(new FormattingChannel(pPatternFormatter2));
    AutoPtr<FileChannel> pFileChannel(new FileChannel("application.log"));
    pFileChannel->setProperty("rotation", "2 M");
    pFileChannel->setProperty("archive", "timestamp");
    pFCFile->setChannel(pFileChannel);
    pFCFile->open();
    Logger& fileLogger = Logger::create("FileLogger", pFCFile, Message::PRIO_TRACE);
    return fileLogger;
}

Logger& AppLogger::log = setUp();
}

