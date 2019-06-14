#include "myConsoleStream.h"

MyConsoleStream::MyConsoleStream(std::ostream &stream, QTextEdit* text_edit):std::basic_streambuf<char>()
  ,m_stream(stream)
{
    this->log_window = text_edit;
    this->m_old_buf = stream.rdbuf();

    stream.rdbuf(this);
}
MyConsoleStream::~MyConsoleStream()
{
    this->m_stream.rdbuf(this->m_old_buf);
}

void MyConsoleStream::registerMyConsoleMessageHandler()
{
    qInstallMessageHandler(myConsoleMessageHandler);
}


void MyConsoleStream::myConsoleMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg)
{

    QByteArray localMsg = msg.toLocal8Bit();
       switch (type) {
       case QtDebugMsg:
          // fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           break;
       case QtInfoMsg:
          // fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           break;
       case QtWarningMsg:
          // fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           break;
       case QtCriticalMsg:
           //fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           break;
       case QtFatalMsg:
          // fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
           break;
       default:
            std::cout << msg.toStdString().c_str();
           break;

       }
}
std::streamsize MyConsoleStream::xsputn(const char *p, std::streamsize n){
    m_string.append(p, p + n);
    long pos = 0;
    while (pos != static_cast<long>(std::string::npos))
    {
        pos = static_cast<long>(m_string.find('\n'));
        if (pos != static_cast<long>(std::string::npos))
        {
            std::string tmp(m_string.begin(), m_string.begin() + pos);
            emit sendLogString(QString::fromStdString(tmp));
            m_string.erase(m_string.begin(), m_string.begin() + pos + 1);
        }
    }
    return n;
}
