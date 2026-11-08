#ifndef MACROS_H
#define MACROS_H

#define CREATE_SCENE(widgetName, exampleName) \
    connect(uiw->widgetName, SIGNAL(clicked()), this, SLOT(exampleName()));

#endif // MACROS_H
