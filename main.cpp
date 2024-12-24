#include "main.h"
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include "main.moc"

VideoToGifApp::VideoToGifApp() {
    QVBoxLayout *layout = new QVBoxLayout(this);

    QLabel *label = new QLabel("Sélectionnez un fichier vidéo :", this);
    QPushButton *selectButton = new QPushButton("Choisir un fichier", this);
    QPushButton *convertButton = new QPushButton("Convertir en GIF", this);
    fileLabel = new QLabel("Aucun fichier sélectionné", this);

    layout->addWidget(label);
    layout->addWidget(selectButton);
    layout->addWidget(fileLabel);
    layout->addWidget(convertButton);

    connect(selectButton, &QPushButton::clicked, this, &VideoToGifApp::selectFile);
    connect(convertButton, &QPushButton::clicked, this, &VideoToGifApp::convertToGif);
}

void VideoToGifApp::selectFile() {
    QString file = QFileDialog::getOpenFileName(this, "Sélectionner une vidéo", "", "Vidéos (*.mp4 *.mkv *.avi)");
    if (!file.isEmpty()) {
        filePath = file;
        fileLabel->setText("Fichier sélectionné : " + filePath);
    } else {
        fileLabel->setText("Aucun fichier sélectionné");
    }
}

void VideoToGifApp::convertToGif() {
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez d'abord sélectionner un fichier !");
        return;
    }

    QString outputGif = filePath.section('.', 0, 0) + ".gif";
    QString command = QString("ffmpeg -i \"%1\" -vf scale=320:240 \"%2\"").arg(filePath, outputGif);

    QProcess process;
    process.start(command);
    process.waitForFinished();

    if (process.exitCode() == 0) {
        QMessageBox::information(this, "Succès", "Conversion terminée : " + outputGif);
    } else {
        QMessageBox::critical(this, "Erreur", "La conversion a échoué !");
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    VideoToGifApp window;
    window.setWindowTitle("Convertisseur Vidéo en GIF");
    window.resize(400, 200);
    window.show();

    return app.exec();
}
