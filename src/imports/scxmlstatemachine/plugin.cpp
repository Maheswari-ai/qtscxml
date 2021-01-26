/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtScxml module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
****************************************************************************/

#include "statemachineloader_p.h"
#include "eventconnection_p.h"
#include "qscxmlevent.h"
#include "statemachineextended_p.h"
#include "invokedservices_p.h"

#include <qqmlextensionplugin.h>
#include <qqml.h>

QT_BEGIN_NAMESPACE

class QScxmlStateMachinePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QScxmlStateMachinePlugin(QObject *parent = nullptr) : QQmlExtensionPlugin(parent) { }
    void registerTypes(const char *uri)
    {
        // @uri QtScxml
        Q_ASSERT(uri == QStringLiteral("QtScxml"));

        int major = 5;
        int minor = 8;
        // Do not rely on RegisterMethodArgumentMetaType meta-call to register the QScxmlEvent type.
        // This registration is required for the receiving end of the signal emission that carries
        // parameters of this type to be able to treat them correctly as a gadget. This is because the
        // receiving end of the signal is a generic method in the QML engine, at which point it's too late
        // to do a meta-type registration.
        static const int qScxmlEventMetaTypeId = qMetaTypeId<QScxmlEvent>();
        Q_UNUSED(qScxmlEventMetaTypeId)
        qmlRegisterType<QScxmlStateMachineLoader>(uri, major, minor, "StateMachineLoader");
        qmlRegisterType<QScxmlEventConnection>(uri, major, minor, "EventConnection");
        qmlRegisterType<QScxmlInvokedServices>(uri, major, minor, "InvokedServices");
        qmlRegisterExtendedUncreatableType<QScxmlStateMachine, QScxmlStateMachineExtended>(
                    uri, major, minor, "StateMachine", "Only created through derived types");

        // Auto-increment the import to stay in sync with ALL future QtQuick minor versions
        qmlRegisterModule(uri, major, QT_VERSION_MINOR);

        qmlProtectModule(uri, 1);
    }
};

QT_END_NAMESPACE

#include "plugin.moc"
