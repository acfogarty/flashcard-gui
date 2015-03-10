#ifndef GRAMMARFLASHCARDDIALOG_H
#define GRAMMARFLASHCARDDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QRadioButton>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QHBoxLayout>
#include <QButtonGroup>

class GrammarFlashcardDialog : public QDialog
{
    Q_OBJECT

public:
    GrammarFlashcardDialog(QWidget* parent = 0);
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *loadButton;
    QLabel *questionLabel;
    QHBoxLayout *horizontalLayout_3;
    QLabel *userAnswerLabel;
    QLineEdit *answerLineEdit;
    QRadioButton *caseAkkRadioButton;
    QRadioButton *caseDatRadioButton;
    QRadioButton *caseGenRadioButton;
    QPushButton *checkButton;
    QHBoxLayout *horizontalLayout_4;
    QLabel *answerLabel;
    QLabel *tickLabel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QMap<QString,QStringList> flashcardMap;
    std::vector<QString> flashcardVector;

    void setCurrentPosition(std::vector<QString>::iterator i);
    std::vector<QString>::iterator getCurrentPosition();
    void resetView();

private:
    std::vector<QString>::iterator currPos;

public slots:
    void loadFlashcardMap(); 
    bool checkAnswer();
    void loadPrevFlashcard();
    void loadNextFlashcard();

};

#endif // GRAMMARFLASHCARDDIALOG_H

