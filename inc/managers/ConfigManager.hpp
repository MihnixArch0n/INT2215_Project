#ifndef CONFIGMANAGER_HPP
#define CONFIGMANAGER_HPP


class ConfigManager
{
public:
    ConfigManager(const ConfigManager&) = delete;
    ConfigManager& operator=(const ConfigManager&) = delete;

    static ConfigManager& getInstance();

    [[nodiscard]] bool getMusicStatus() const {return musicStatus;}
    [[nodiscard]] bool getSoundStatus() const {return soundStatus;}
    [[nodiscard]] int getMusicVolume() const {return musicVolume;}
    [[nodiscard]] int getSoundVolume() const {return soundVolume;}

    void toogleMusic(bool opt) {musicStatus = opt;}
    void toogleSound(bool opt) {soundStatus = opt;}
    void setMusicVolume(int vol) {musicVolume = vol;}
    void setSoundVolume(int vol) {soundVolume = vol;}

    void save() const;
    void load();
private:
    ConfigManager();
    ~ConfigManager();

    bool musicStatus = true;
    bool soundStatus = true;
    int musicVolume = 10;
    int soundVolume = 10;
};



#endif //CONFIGMANAGER_HPP
