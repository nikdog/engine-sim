#include "../include/yds_file_logger.h"
#include <cstring>

ysFileLogger::ysFileLogger() : ysLoggerOutput("ysFileLogger") {
    /* void */
}

ysFileLogger::~ysFileLogger() {
    /* void */
}

void ysFileLogger::OpenFile(const char *fname) {
#ifdef _MSC_VER
    strcpy_s(m_fname, 256, fname);
#else
    strncpy(m_fname, fname, 255);
    m_fname[255] = '\0';
#endif
}

void ysFileLogger::Initialize() {
    m_stream.open(m_fname, std::ios::out);
}

void ysFileLogger::Close() {
    m_stream.close();
}

void ysFileLogger::Write(const char *data) {
    m_stream.write(data, strlen(data));
}
