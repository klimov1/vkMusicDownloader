#include "widget.h"
#include "ui_widget.h"

#include "request.h"
#include "audio.h"
#include "config.h"
#include "downloadmanager.h"

#include <QStandardItemModel>

namespace {

class NonEditableModel : public QStandardItemModel
{

    Qt::ItemFlags flags(const QModelIndex &/*index*/) const override
    {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled ;
    }
public:
    NonEditableModel(int rowCount, Widget* parent) : QStandardItemModel(rowCount, 1, parent)
    {}

};

} // anonymous

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QIntValidator* validator = new QIntValidator(0, 3000, this);
    ui->songCountEdit->setValidator(validator);
    connect(ui->songCountEdit,SIGNAL(textChanged(QString)),this,SLOT(songCountChanged(QString)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::songCountChanged(QString text)
{
    songCount_ = text.toInt();
}

void Widget::initSongListView(const std::vector<audio::SongInfo>& songs)
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

    ui->songListView->setModel(model);
    ui->songListView->setViewMode( QListView::ListMode );

    connect(ui->songListView, &QListView::clicked, this,[songs](const QModelIndex &index)
            {
        auto& song = songs[index.row()];
        DownloadManager::getInstance().addToQueue(song.title_+".mp3",song.url_);
    } );
}

void Widget::on_getAudiosBtn_clicked()
{
    initSongListView(audio::getSongs(Config::getInstance().getUserId(), static_cast<std::size_t>(songCount_)));
}
