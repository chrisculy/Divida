QT	   -= core gui

TARGET = divida
TEMPLATE = lib
CONFIG += staticlib
PRECOMPILED_HEADER=pch.h
INCLUDEPATH+=../external/pugixml/include

SOURCES += \
	Beneficiary.cpp \
	BeneficiarySerializer.cpp \
	Core.cpp \
	Date.cpp \
	Expense.cpp \
	Item.cpp \
	Object.cpp \
	ObjectSerializer.cpp \
	Person.cpp \
	PersonSerializer.cpp \
	Report.cpp \
	ReportXmlSerializer.cpp \
	Transaction.cpp \
	Exception.cpp

HEADERS += \
	Beneficiary.h \
	BeneficiarySerializer.h \
	Core.h \
	Date.h \
	Expense.h \
	Item.h \
	IXmlSerializer.h \
	Object.h \
	ObjectSerializer.h \
	pch.h \
	Person.h \
	PersonSerializer.h \
	Report.h \
	ReportXmlSerializer.h \
	Transaction.h \
	Exception.h
unix {
	target.path = /usr/lib
	INSTALLS += target
	QMAKE_CXXFLAGS+=-std=c++1y -stdlib=libc++
}
win32-g++ {
	QMAKE_CXXFLAGS+=-std=c++11
}
