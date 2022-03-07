class SDLSetup {
    public:
        static SDLSetup& getInstance()
        {
            static SDLSetup instance;
            return instance;
        }
};