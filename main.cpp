#include <QApplication>
#include <QDialog>

#include "GrammarFlashcardDialog.h"

int main(int argc, char *argv[])
{
   QApplication app(argc, argv);
   GrammarFlashcardDialog grammarFlashcardDialog;
   grammarFlashcardDialog.show();
   return app.exec();
}

