#include "../headers/MainWindow.hpp"
#include <QToolBar>
#include <QLayout>
#include <QMenu>
#include <QSlider>
#include <QSpinBox>
#include <QMenuBar>
#include <QFileDialog>
#include <filesystem>
#include <iostream>

music_player::music_player(int argc, char** argv, QWidget* parent) : QMainWindow(parent) {
    setup_ui();

    g_mgr_ = std::make_unique<gstreamer_mgr>(argc, argv);

    connect(file_menu, &QMenu::triggered, this, [&] (QAction* act) {
        if(act->text() == "Open") {
            selected_file_ = QFileDialog::getOpenFileName(this, "Select a sound", std::filesystem::current_path().string().c_str(), "*.wav, *.mp3");
            update_ui_on_file();
            g_mgr_->load_audio(selected_file_.toStdString());
        }
        else 
            std::cout << act->text().toStdString();
    });

    connect(play, &QPushButton::clicked, g_mgr_.get(), &gstreamer_mgr::play);
    connect(pause, &QPushButton::clicked, g_mgr_.get(), &gstreamer_mgr::pause);

    setCentralWidget(main_widget_);

    setMinimumSize(700, 500);

    update_ui_on_file();
}

void music_player::setup_ui() {
    main_widget_ = new QWidget(this);

    QMenuBar *menu = new QMenuBar(main_widget_);

    file_menu = new QMenu("&File");
    file_menu->addAction("Open");

    pause = new QPushButton(this);
    play = new QPushButton(this);

    duration = new QLabel("00:00:00/00:00:00");
    song_name = new QLabel;

    edit_menu = new QMenu("&Edit");

    menu->addMenu(file_menu);
    menu->addMenu(edit_menu);

    slider_ = new QSlider(Qt::Horizontal, this);

    pause->setIcon(QIcon(":/resources/pause.png"));
    play->setIcon(QIcon(":/resources/play.png"));

    main_layout_= new QVBoxLayout(main_widget_);
    layout_ = new QHBoxLayout();
    layout_down_ = new QHBoxLayout();
    main_layout_->addLayout(layout_);
    main_layout_->addLayout(layout_down_);

    layout_->addWidget(play);
    layout_->addWidget(pause);
    layout_->addWidget(slider_);
    layout_->addWidget(duration);

    layout_down_->addWidget(song_name);
}

void music_player::update_ui_on_file() {
    const bool song_loaded = !selected_file_.isEmpty();
    pause->setDisabled(true);
    play->setEnabled(song_loaded);
    slider_->setEnabled(song_loaded);

    song_name->setText(selected_file_);
}