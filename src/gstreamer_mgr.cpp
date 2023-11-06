#include "../headers/gstreamer_mgr.hpp"
#include <QDebug>

gstreamer_mgr::gstreamer_mgr(int argc, char** argv, QObject* parent) : QObject(parent) {
    gst_init (&argc, &argv);
}

void gstreamer_mgr::load_audio(const std::filesystem::path& p) {
    const std::string str = "playbin uri=file://" + p.string();
    pipeline =
      gst_parse_launch
      (str.c_str(),
      NULL);
}

void gstreamer_mgr::play() {
    if(pipeline) {
        gst_element_set_state (pipeline, GST_STATE_PLAYING);

        /* Wait until error or EOS */
        //bus = gst_element_get_bus (pipeline);
        //msg =
        //gst_bus_timed_pop_filtered (bus, GST_CLOCK_TIME_NONE,
        //GstMessageType((GST_MESSAGE_ERROR | GST_MESSAGE_EOS)));

  /* See next tutorial for proper error message handling/parsing */
        //if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ERROR) {
        //    g_error ("An error occurred! Re-run with the GST_DEBUG=*:WARN environment "
        //    "variable set for more details.");
        //}
    }
    else {
        qDebug() << "no pipeline";
    }
}

void gstreamer_mgr::pause() {
    if(pipeline) {
        gst_element_set_state (pipeline, GST_STATE_PAUSED);
    }
}

gstreamer_mgr::~gstreamer_mgr() {
    gst_message_unref (msg);
    gst_object_unref (bus);
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
}