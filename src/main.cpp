#include <QWidget>
#include <QApplication>
#include <QDialog>
#include <QLabel>
#include "gst/gst.h"

#include <memory>

#include "../headers/MainWindow.hpp"

int main(int argc, char** argv) {
    // QApplication app(argc, argv);

    // auto mw = std::make_unique<music_player>(argc, argv);
    // mw->show();

    // return app.exec();
    GstElement *pipeline, *source, *decoder, *sink;
    GstBus *bus;
    GstMessage *msg;
    GMainLoop *loop;

    // Initialize GStreamer
    gst_init(&argc, &argv);

    // Create a GMainLoop
    loop = g_main_loop_new(NULL, FALSE);

    // Create the elements
    pipeline = gst_pipeline_new("audio-player");
    source = gst_element_factory_make("filesrc", "file-source");
    decoder = gst_element_factory_make("mad", "mp3-decoder"); // Using mad plugin for MP3 decoding
    sink = gst_element_factory_make("autoaudiosink", "audio-output");

    if (!pipeline || !source || !decoder || !sink) {
        g_printerr("Not all elements could be created. Exiting.\n");
        if(!pipeline) {
            g_printerr("!pipeline\n");
        }
        if(!source) {
            g_printerr("!source\n");
        }
        if(!decoder) {
            g_printerr("!decoder\n");
        }
        if(!sink) {
            g_printerr("!sink\n");
        }
        return -1;
    }

    // Set the input audio file
    g_object_set(source, "location", "/home/Downloads/in_the_end.mp3", NULL);

    // Add elements to the pipeline
    gst_bin_add_many(GST_BIN(pipeline), source, decoder, sink, NULL);
    if (gst_element_link_many(source, decoder, sink, NULL) != TRUE) {
        g_printerr("Elements could not be linked. Exiting.\n");
        gst_object_unref(pipeline);
        return -1;
    }

    // Set the pipeline to "playing" state
    g_print("Now playing: your_audio.mp3\n");
    gst_element_set_state(pipeline, GST_STATE_PLAYING);

    // Create a bus to listen for messages
    bus = gst_element_get_bus(pipeline);

    // Start a GMainLoop to wait for events
    g_main_loop_run(loop);

    // Clean up resources
    gst_element_set_state(pipeline, GST_STATE_NULL);
    gst_object_unref(GST_OBJECT(pipeline));
    g_main_loop_unref(loop);

    return 0;
}