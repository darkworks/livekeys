#include "qmllanguageobject.h"

namespace lv{

QmlLanguageObject::QmlLanguageObject(void *language, QObject *parent)
    : QObject(parent)
    , m_language(language)
{
}

}// namespace
