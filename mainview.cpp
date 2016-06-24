#include "mainview.h"

#include "request.h"
#include "audio.h"
#include "config.h"
#include "downloadmanager.h"

#include <QStandardItemModel>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace {

class NonEditableModel : public QStandardItemModel
{

    Qt::ItemFlags flags(const QModelIndex &/*index*/) const override
    {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
    }
public:
    NonEditableModel(int rowCount, QWidget* parent) : QStandardItemModel(rowCount, 1, parent)
    {}

};

} // anonymous

MainView::MainView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout();

    QHBoxLayout* songCountLayout = new QHBoxLayout();
    getAudiosBtn_ = new QPushButton("Get list of songs", this);
    songCountEdit_ = new QLineEdit("50", this);
    songListView_ = new QListView(this);

    songCountLayout->addWidget(getAudiosBtn_);
    songCountLayout->addWidget(songCountEdit_);

    QIntValidator* validator = new QIntValidator(0, 3000, this);
    songCountEdit_->setValidator(validator);

    connect(songCountEdit_,SIGNAL(textChanged(QString)),this,SLOT(songCountChanged(QString)));
    connect(getAudiosBtn_, SIGNAL(clicked(bool)), this, SLOT(getAudiosBtnClicked()));

    mainLayout->addLayout(songCountLayout);
    mainLayout->addWidget(songListView_);

    setLayout(mainLayout);
}

void MainView::getAudiosBtnClicked()
{
    initSongListView(audio::getSongs(Config::getInstance().getUserId(), static_cast<std::size_t>(songCount_)));
}

void MainView::songCountChanged(QString text)
{
    songCount_ = text.toInt();
}

void MainView::initSongListView(const std::vector<audio::SongInfo>& songs)
{
    int rowCount = static_cast<int>(songs.size());
    auto* model = new NonEditableModel(rowCount, this);
    for (int row = 0; row < rowCount; ++row)
    {
        QModelIndex nameIndex = model->index(row,0);
        QString songName = songs[row].artist_ + " - "+ songs[row].title_;
        nameIndex.flags();

        model->setData(nameIndex, songName, Qt::DisplayRole);
        model->setData(nameIndex, songName, Qt::ToolTipRole);
        model->setData(nameIndex, QIcon(":/images/download.jpg"), Qt::DecorationRole);
    }

    songListView_->setModel(model);
    songListView_->setViewMode( QListView::ListMode );

    connect(songListView_, &QListView::clicked, this,[songs](const QModelIndex &index)
            {
                auto& song = songs[index.row()];
                DownloadManager::getInstance().addToQueue(song.title_+".mp3",song.url_);
    } );
}

