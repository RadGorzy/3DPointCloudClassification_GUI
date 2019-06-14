//from : https://stackoverflow.com/questions/9211298/redirect-stdcout-to-qtextedit
#ifndef MYCONSOLESTREAM_H
#define MYCONSOLESTREAM_H
#include <iostream>
#include <QTextEdit>
class MyConsoleStream:public std::basic_streambuf<char>
{
public:
    MyConsoleStream(std::ostream &stream, QTextEdit* text_edit);
    virtual ~MyConsoleStream();
    static void registerMyConsoleMessageHandler();

private:
    std::ostream &m_stream;
    std::streambuf *m_old_buf;
    QTextEdit* log_window;

    static void myConsoleMessageHandler(QtMsgType type, const QMessageLogContext &, const QString &msg);
protected:
    //This function is called when std::endl appears in the stream
    virtual int_type overflow(int_type v)
    {
        if (v == '\n')
        {
            log_window->append("");
        }
        return v;
    }

    virtual std::streamsize xsputn(const char *p, std::streamsize n);
};

#endif // MYCONSOLESTREAM_H
