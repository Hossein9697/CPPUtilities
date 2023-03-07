#include "data-verification/DataVerification.h"

#include <QByteArray>
#include <QCryptographicHash>
#include <QDebug>
#include <QFile>
#include <QTextStream>

DataVerification::ReturnCodes DataVerification::createVerificationFilesFromFileOfPaths(const std::string& thePathOfFilePathes)
{
    QFile inputFile(thePathOfFilePathes.c_str());

    if (inputFile.open(QIODevice::ReadOnly))
    {
        /* create hash file of main list file*/
        QByteArray mainListHashResult = QCryptographicHash::hash(inputFile.readAll(), QCryptographicHash::Algorithm::Md5);
        QString hashFilePath = inputFile.fileName() + ".Md5";
        QFile hashFile(hashFilePath);
        if (!hashFile.open(QFile::ReadWrite | QFile::Text))
        {
            qDebug() << "could not open mainhashfile to write hash code";
            qDebug() << hashFile.errorString();
            hashFile.close();
            return ReturnCodes::COULD_NOT_OPEN_MAIN_HASH_FILE;
        }
        hashFile.write(mainListHashResult);
        hashFile.close();

        inputFile.reset();
        /**/
        QTextStream in(&inputFile);

        while (!in.atEnd())
        {
            QString line = in.readLine();

            qDebug() << line;

            QFile currentFile(line);

            if (!currentFile.open(QFile::ReadOnly | QFile::Text))
            {
                qDebug() << "error, file not exist \n";
                continue;
            }

            QTextStream in(&currentFile);

            QString dataToHash = in.readAll();

            QByteArray hashDataArray(dataToHash.toStdString().c_str());

            QByteArray hashResult = QCryptographicHash::hash(hashDataArray, QCryptographicHash::Algorithm::Md5);

            // qDebug() << strHashResult;

            QString hashFilePath = currentFile.fileName() + ".Md5";

            QFile hashFile(hashFilePath);

            qDebug() << hashFile.fileName();

            if (!hashFile.open(QFile::ReadWrite | QFile::Text))
            {
                qDebug() << "error:" << currentFile.fileName() << " could not created.";
                qDebug() << currentFile.errorString();
                currentFile.close();
                continue;
            }

            hashFile.write(hashResult);

            hashFile.close();
            currentFile.close();
        }

        inputFile.close();
    }
    else
    {
        qDebug() << "list file not exist \n";
        return DataVerification::ReturnCodes::INPUT_FILE_PATH_NOT_EXIST;
    }
}

DataVerification::ReturnCodes DataVerification::verifyAllConfigFiles(const std::string& thePathOfFilePathes)
{
    /* open paths file */
    QFile pathFile(thePathOfFilePathes.c_str());

    if (!pathFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "list file not exist \n";
        return DataVerification::ReturnCodes::INPUT_FILE_PATH_NOT_EXIST;
    }

    /* calc hash of paths file */
    QTextStream in(&pathFile);
    QString dataToHash = in.readAll();
    QByteArray hashDataArray(dataToHash.toStdString().c_str());
    QByteArray calculatedHashCode = QCryptographicHash::hash(hashDataArray, QCryptographicHash::Algorithm::Md5);

    /* open verify paths file */
    QFile hashPathFile((thePathOfFilePathes + ".Md5").c_str());

    if (!hashPathFile.open(QIODevice::ReadOnly))
    {
        qDebug() << "verify list file not exist \n";
        pathFile.close();
        return DataVerification::ReturnCodes::INPUT_FILE_PATH_NOT_EXIST;
    }

    /* read previous calculated hash */
    QByteArray previousHashCode = hashPathFile.readAll();

    /* compare two hash code */
    if (previousHashCode != calculatedHashCode)
    {
        qDebug() << "path and verify path file hash not equal";
        pathFile.close();
        hashPathFile.close();
        return DataVerification::ReturnCodes::HASH_NOT_EQUAL;
    }

    hashPathFile.close();

    QTextStream records(&dataToHash);

    /* start to verify all config files */
    while (!records.atEnd())
    {

        QString line = records.readLine();

        qDebug() << line;

        QFile currentFile(line);
        QFile currentVerifyFile(line + ".Md5");

        if ((!currentFile.open(QFile::ReadOnly | QFile::Text)) || (!currentVerifyFile.open(QFile::ReadOnly)))
        {
            qDebug() << "error, files not exist \n";
            pathFile.close();
            return DataVerification::ReturnCodes::INPUT_FILE_PATH_NOT_EXIST;
        }

        /* calc current file hash code */
        QTextStream in(&currentFile);
        QString dataToHash = in.readAll();
        QByteArray hashDataArray(dataToHash.toStdString().c_str());
        QByteArray calculatedHashCode = QCryptographicHash::hash(hashDataArray, QCryptographicHash::Algorithm::Md5);

        /* read previous hash code*/
        QByteArray previousHashCode = currentVerifyFile.readAll();

        /* compare two hash code */
        if (previousHashCode != calculatedHashCode)
        {
            qDebug() << "path and verify path file hash not equal";
            pathFile.close();
            currentFile.close();
            return DataVerification::ReturnCodes::HASH_NOT_EQUAL;
        }

        currentFile.close();
    }
    pathFile.close();
    return DataVerification::ReturnCodes::OK;
}
