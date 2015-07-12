#include "virtualroom.h"

#include "polygoncameratopology.h"

VirtualRoom::VirtualRoom(RoomSettings *settings, QObject *parent) :
    IVirtualRoom(settings, parent)
{
    setSettings(settings);

    m_cameraTopology = new PolygonCameraTopology(settings);

    connect(m_cameraTopology, &ICameraTopology::frameReady, this, &VirtualRoom::handleFrameFromTopology);
}

VirtualRoom::~VirtualRoom()
{

}

void VirtualRoom::recordScene(bool record)
{
    m_cameraTopology->record(record);
}

void VirtualRoom::recordAnimation(bool record)
{
    if(! m_settings->recordScene())
    {
        return;
    }

    if(record)
    {
        Animation *anim = new Animation();
        connect(m_cameraTopology, &ICameraTopology::frameReady, anim, &Animation::addFrame);

        m_animations.push_back(anim);
    }
    else
    {
        m_cameraTopology->disconnect(m_animations.last(), 0);

        emit animationRecorded(m_animations.last());
    }
}

void VirtualRoom::handleFrameFromTopology(Frame frame)
{

}

QVariantMap VirtualRoom::toVariantMap()
{

}

void VirtualRoom::fromVariantMap(QVariantMap varMap)
{

}

void VirtualRoom::settingsChange(RoomSettings::RoomSettingsType type)
{
    switch (type) {
    case RoomSettings::RoomSettingsType::RECORD:
        recordScene(m_settings->recordScene());
        break;
    case RoomSettings::RoomSettingsType::RECORDANIMATION:
        recordAnimation(m_settings->recordAnimation());
        break;
    default:
        break;
    }
}
