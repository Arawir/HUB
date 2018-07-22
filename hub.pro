QT += core widgets network
requires(qtConfig(combobox))

HEADERS       = Server/Inc/client.hh \
                Server/Inc/server.hh \
                Mainapp/Inc/player.hh \
                Mainapp/Inc/main_app.hh
                
SOURCES       = Server/Src/client.cpp \
                Server/Src/server.cpp \
                Mainapp/Src/player.cpp \
                Mainapp/Src/main_app_a.cpp \
                Mainapp/Src/main_app_b.cpp \
                Mainapp/Src/main.cpp

release: DESTDIR = Bin
OBJECTS_DIR = .obj        
MOC_DIR = .moc
RCC_DIR = .qrc
UI_DIR = .ui


# install
target.path = $$[QT_INSTALL_EXAMPLES]/network/fortuneclient
INSTALLS += target
