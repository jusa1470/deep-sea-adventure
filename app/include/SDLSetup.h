class SDLSetup {
    public:
        static SDLSetup* getInstance()
        {
            static SDLSetup *instance;
            return instance;
        }
    private:
        SDLSetup() {};
        SDLSetup(SDLSetup const&);
        void operator=(SDLSetup const&);
};