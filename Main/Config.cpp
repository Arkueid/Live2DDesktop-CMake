#include "Config.hpp"
#include <QtCore/qjsonobject.h>

#include <QtCore/qjsondocument.h>
#include <QtCore/qfile.h>
#include <Default.hpp>

#include <utils/Log.hpp>

static QJsonObject _json;

bool Config::Initialize()
{
    QFile file;
    file.setFileName(APP_CONFIG_PATH);
    file.open(QFile::ReadOnly);
    if (!file.exists())
    {
        GenerateDefaultConfig();
        SaveConfig();
        Info("generate new config : %s", APP_CONFIG_PATH);
        return true;
    }

    if (!file.isOpen())
    {
        Error("file open error: %s", APP_CONFIG_PATH);
        return false;
    }
    QByteArray bytes = file.readAll();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(bytes, &error);
    if (error.error != QJsonParseError::NoError)
    {
        Error("文件解析错误: %s", error.errorString().toStdString().c_str());
        return false;
    }
    _json = doc.object();
    return true;
}

bool Config::GenerateDefaultConfig()
{
    _json = QJsonObject();

    SetResourceDir(APP_RESOURCE_DIR);
    SetSceneWidth(APP_SCENE_WIDTH);
    SetSceneHeight(APP_SCENE_HEIGHT);
    SetSceneVisible(APP_SCENE_VISIBLE);
    SetSceneStayOnTop(APP_SCENE_STAY_ON_TOP);
    SetModelName(APP_MODEL_NAME);
    SetSysTrayIconPath(APP_SYS_TRAY_ICON_PATH);
    SetMouseTrack(APP_MOUSE_TRACK);
    SetMouseEventsTransparent(APP_MOUSE_EVENTS_TRANSPARENT);
    return true;
}

bool Config::SaveConfig()
{
    QFile file;
    file.setFileName(APP_CONFIG_PATH);
    file.open(QFile::ReadWrite);
    if (!file.isOpen())
    {
        Error("file open error: %s", APP_CONFIG_PATH);
        return false;
    }

    QJsonDocument doc(_json);

    file.write(doc.toJson());
    file.close();
    return true;
}

std::string Config::GetResourceDir()
{
    return _json.value(KEY_RESOURCE_DIR).toString().toStdString();
}

int Config::GetSceneWidth()
{
    return _json.value(KEY_SCENE).toObject().value(KEY_SCENE_WIDTH).toInt();
}

int Config::GetSceneHeight()
{
    return _json.value(KEY_SCENE).toObject().value(KEY_SCENE_HEIGHT).toInt();
}

bool Config::GetSceneVisible()
{
    return _json.value(KEY_SCENE).toObject().value(KEY_SCENE_VISIBLE).toBool();
}

bool Config::GetSceneStayOnTop()
{
    return _json.value(KEY_SCENE).toObject().value(KEY_SCENE_STAY_ON_TOP).toBool();
}

std::string Config::GetModelName()
{
    return _json.value(KEY_MODEL).toObject().value(KEY_MODEL_NAME).toString().toStdString();
}

void Config::SetSysTrayIconPath(std::string iconPath)
{
    QJsonObject systray = _json.value(KEY_SYS_TRAY).toObject();
    systray[KEY_SYS_TRAY_ICON_PATH] = iconPath.c_str();
    _json[KEY_SYS_TRAY] = systray;
}

std::string Config::GetSysTrayIconPath()
{
    return _json.value(KEY_SYS_TRAY).toObject().value(KEY_SYS_TRAY_ICON_PATH).toString().toStdString();
}

void Config::SetMouseTrack(bool enable)
{
    QJsonObject mouse = _json.value(KEY_MOUSE).toObject();
    mouse[KEY_MOUSE_TRACK] = enable;
    _json[KEY_MOUSE] = mouse;
}

void Config::SetMouseEventsTransparent(bool enable)
{
    QJsonObject mouse = _json.value(KEY_MOUSE).toObject();
    mouse[KEY_MOUSE_EVENTS_TRANSPARENT] = enable;
    _json[KEY_MOUSE] = mouse;
}

bool Config::GetMouseTrack()
{
    return _json.value(KEY_MOUSE).toObject().value(KEY_MOUSE_TRACK).toBool();
}

bool Config::GetMouseEventsTransparent()
{
    return _json.value(KEY_MOUSE).toObject().value(KEY_MOUSE_EVENTS_TRANSPARENT).toBool();
}

void Config::SetResourceDir(std::string resource_dir)
{
    _json[KEY_RESOURCE_DIR] = resource_dir.c_str();
}

void Config::SetSceneWidth(int width)
{
    QJsonObject scene = _json[KEY_SCENE].toObject();
    scene[KEY_SCENE_WIDTH] = width;
    _json[KEY_SCENE] = scene;
}

void Config::SetSceneHeight(int height)
{
    QJsonObject scene = _json[KEY_SCENE].toObject();
    scene[KEY_SCENE_HEIGHT] = height;
    _json[KEY_SCENE] = scene;
}

void Config::SetSceneVisible(bool visible)
{
    QJsonObject scene = _json[KEY_SCENE].toObject();
    scene[KEY_SCENE_VISIBLE] = visible;
    _json[KEY_SCENE] = scene;
}

void Config::SetSceneStayOnTop(bool enable)
{
    QJsonObject scene = _json[KEY_SCENE].toObject();
    scene[KEY_SCENE_STAY_ON_TOP] = enable;
    _json[KEY_SCENE] = scene;
}

void Config::SetModelName(std::string name)
{
    QJsonObject model = _json[KEY_MODEL].toObject();
    model[KEY_MODEL_NAME] = name.c_str();
    _json[KEY_MODEL] = model;
}

