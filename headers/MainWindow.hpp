#pragma once
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QLayout>
#include <QSlider>
#include <QString>
#include <QPushButton>
#include <QLabel>
#include "gstreamer_mgr.hpp"

class music_player : public QMainWindow {
    Q_OBJECT
    public:
        music_player(int argc, char** argv, QWidget* parent = nullptr);
        virtual ~music_player() {}
    private:
        void update_ui_on_file();

        void setup_ui();

        std::unique_ptr<gstreamer_mgr> g_mgr_;

        QAction* file_action_;
        QMenu* file_menu;
        QMenu* edit_menu;

        QWidget* main_widget_;

        QString selected_file_;

        QSlider* slider_;

        QLabel* duration;
        QLabel* song_name;

        QPushButton *pause, *play;

        QHBoxLayout* layout_;
        QHBoxLayout* layout_down_;
        QVBoxLayout* main_layout_;
};