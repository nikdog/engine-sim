#include "../include/yds_render_geometry_format.h"
#include <cstring>

ysRenderGeometryFormat::ysRenderGeometryFormat() : ysObject("RENDER_GEOMETRY_FORMAT") {
    m_formatSize = 0;
}

ysRenderGeometryFormat::~ysRenderGeometryFormat() {
    /* void */
}

int ysRenderGeometryFormat::GetChannelCount() const {
    return m_channels.GetNumObjects();
}

int ysRenderGeometryFormat::GetFormatSize() const {
    return m_formatSize;
}

void ysRenderGeometryFormat::AddChannel(const char *name, int offset, ysRenderGeometryChannel::ChannelFormat format) {
    ysRenderGeometryChannel *newChannel = m_channels.New();
#ifdef _MSC_VER
    strcpy_s(newChannel->m_name, ysRenderGeometryChannel::MAX_NAME_LENGTH, name);
#else
    strncpy(newChannel->m_name, name, ysRenderGeometryChannel::MAX_NAME_LENGTH - 1);
    newChannel->m_name[ysRenderGeometryChannel::MAX_NAME_LENGTH - 1] = '\0';
#endif
    newChannel->m_format = format;
    newChannel->m_offset = offset;

    m_formatSize += newChannel->GetSize();
}
