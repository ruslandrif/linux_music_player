#pragma once
#include <utility>
#include <filesystem>
#include <QObject>
//#include <gst/gst.h>
#include "gst/gst.h"

#ifdef __APPLE__
#include <TargetConditionals.h>
#endif

class gstreamer_mgr : public QObject {
    Q_OBJECT
    public:
        gstreamer_mgr(int argc, char** argv, QObject* parent = nullptr);
        virtual ~gstreamer_mgr();

        void load_audio(const std::filesystem::path& p);
    public slots:
        void play();
        void pause();
    private:
        GstElement *pipeline{ nullptr };
        GstBus *bus{ nullptr };
        GstMessage *msg{ nullptr };
};