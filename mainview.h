#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QListView>


namespace audio {
struct SongInfo;
} // audio

class MainView : public QWidget
{
    Q_OBJECT
public:
    explicit MainView(QWidget *parent = 0);

private slots:

    void getAudiosBtnClicked();
    void songCountChanged(QString);

private:
    void initSongListView( const std::vector<audio::SongInfo>& songs );

private:
    int songCount_ = 50;

private:
    QPushButton* getAudiosBtn_ = nullptr;
    QLineEdit* songCountEdit_ = nullptr;
    QListView* songListView_ = nullptr;
};

#endif // MAINVIEW_H
