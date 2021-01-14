/*
  Copyright (c) 2010 Boris Moiseev (cyberbobs at gmail dot com)

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License version 2.1
  as published by the Free Software Foundation and appearing in the file
  LICENSE.LGPL included in the packaging of this file.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.
*/
// Local
#include "ConsoleAppender.h"

// STL
#include <iostream>

// Termcolor
#include <termcolor.hpp>

/**
 * \class ConsoleAppender
 *
 * \brief ConsoleAppender is the simple appender that writes the log records to the std::cerr output stream.
 *
 * ConsoleAppender uses "[%{type:-7}] <%{function}> %{message}\n" as a default output format. It is similar to the
 * AbstractStringAppender but doesn't show a timestamp.
 *
 * You can modify ConsoleAppender output format without modifying your code by using \c QT_MESSAGE_PATTERN environment
 * variable. If you need your application to ignore this environment variable you can call
 * ConsoleAppender::ignoreEnvironmentPattern(true)
 */

ConsoleAppender::ConsoleAppender()
	: AbstractStringAppender()
	, m_ignoreEnvPattern(false)
{
	setFormat("[%{type:-7}] <%{function}> %{message}\n");
}

QString ConsoleAppender::format() const
{
	const QString envPattern = QString::fromLocal8Bit(qgetenv("QT_MESSAGE_PATTERN"));
	return (m_ignoreEnvPattern || envPattern.isEmpty()) ? AbstractStringAppender::format() : (envPattern + "\n");
}

void ConsoleAppender::ignoreEnvironmentPattern(bool ignore)
{
	m_ignoreEnvPattern = ignore;
}

//! Writes the log record to the std::cerr stream.
/**
 * \sa AbstractStringAppender::format()
 */
void ConsoleAppender::append(const QDateTime &timeStamp, Logger::LogLevel logLevel, const char *file, int line,
                             const char *function, const QString &category, const QString &message)
{
	switch (logLevel)
	{
		case Logger::Trace:
			std::cerr << termcolor::magenta;
			break;
		case Logger::Debug:
			std::cerr << termcolor::green;
			break;
		case Logger::Info:
			std::cerr << termcolor::white;
			break;
		case Logger::Warning:
			std::cerr << termcolor::yellow;
			break;
		case Logger::Error:
			std::cerr << termcolor::red;
			break;
		case Logger::Fatal:
			std::cerr << termcolor::red;
			break;
	}
	std::cerr << qPrintable(formattedString(timeStamp, logLevel, file, line, function, category, message)) << termcolor::reset;
}
