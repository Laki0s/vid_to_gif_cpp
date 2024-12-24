#ifndef VIDEOTOGIFAPP_H
#define VIDEOTOGIFAPP_H

#include <QWidget>
#include <QString>
#include <QLabel>

class VideoToGifApp : public QWidget {
    Q_OBJECT

public:
    VideoToGifApp();
    ~VideoToGifApp();

private slots:
    void selectFile();
    void convertToGif();

private:
    QString filePath;
    QLabel *fileLabel;
};

#endif // VIDEOTOGIFAPP_H
