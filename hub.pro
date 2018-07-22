QT += core widgets network
requires(qtConfig(combobox))

HEADERS       = Server/Inc/client.hh \
                Server/Inc/server.hh 
                
SOURCES       = Server/Src/client.cpp \
                Server/Src/server.cpp \
                Mainapp/Src/main.cpp

release: DESTDIR = Bin
OBJECTS_DIR = .obj        
MOC_DIR = .moc
RCC_DIR = .qrc
UI_DIR = .ui


# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneclient
INSTALLS += target
