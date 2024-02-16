#pragma once
#include <string>
#include <vector>
#include "../../../Memory/GameData.h"
#include "../../../Utils/Keys.h"
class IModule;
enum Category {
	COMBAT = 0,
	VISUAL = 1,
	MOVEMENT = 2,
	PLAYER = 3,
	WORLD = 4,
	MISC = 5,
	CLIENT = 6
};
struct EnumEntry {
private:
public:
	/*const */ std::string name;
	/*const */ unsigned char val;

	/// <summary>Use this however you want</summary>
	void* ptr = nullptr;
	EnumEntry(const std::string _name, const unsigned char value);
	std::string GetName();
	unsigned char GetValue();
};
class SettingEnum {
private:
	IModule* owner = nullptr;

public:
	std::vector<EnumEntry> Entrys;
	int selected = -1;

	SettingEnum(std::vector<EnumEntry> entr, IModule* mod = nullptr);
	SettingEnum(IModule* mod = nullptr);
	//SettingEnum();
	SettingEnum& addEntry(EnumEntry entr);
	EnumEntry& GetEntry(int ind);
	EnumEntry& GetSelectedEntry();
	int GetCount();
};
enum ValueType {
	FLOAT_T,
	DOUBLE_T,
	INT_T,
	BOOL_T,
	TEXT_T,
	ENUM_T
};

struct SettingValue {
	union {
		float _float;
		double _double;
		int _int;
		bool _bool;
		bool Value;
		const char* texts;
		std::string* text;
	};
};
struct SettingEntry {
	char name[0x20] = "";
	ValueType valueType;
	SettingValue* value = nullptr;
	SettingValue* defaultValue = nullptr;
	SettingValue* minValue = nullptr;
	SettingValue* maxValue = nullptr;
	SettingValue* intValue = nullptr;
	SettingValue* floatValue = nullptr;


	void* extraData; // Only used by enum for now

	// ClickGui Data
	bool isDragging = false;  // This is incredibly hacky and i wanted to avoid this as much as possible but i want to get this clickgui done

	void makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt();
};

class IModule {
public:
	bool prev = false;
	bool enabled = false;
	bool extended = false;
	int keybind = 0x0;
	Vec2 ModulePos;
private:
	Category cat;
	const char* desc;
	std::vector<SettingEntry*> settings;
protected:
	IModule(std::string name,int key, Category c, const char* desc);

	void registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue);
	void registerIntSetting(std::string name, int* intpTr, int defaultValue, int minValue, int maxValue);
	void registerEnumSetting(std::string name, SettingEnum* intPtr, int defaultValue);
	void registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue);
public:
	~IModule();
	const int getkey() { return this->keybind; }
	const char* getDesc() { return this->desc; }
	Category getCateg() { return this->cat; }
	std::vector<SettingEntry*> getSettings() { return this->settings; }
	void setEnabled(bool enb);

	//bool isEnabled() { return this->enabled; }
	void checkEnabled();
	//bool isExtended() { return this->extended; }
	virtual const char* getModuleName() = 0;
	virtual const char* getRawModuleName();

	virtual bool isEnabled();
	virtual bool isExtended();
	virtual int getKeybind();
	virtual void setKeybind(int key);
	virtual void onEnable();
	virtual void onDisable();
	virtual void onFrame();
	virtual void onTick(GameMode*);
	virtual void onKeyUpdate(int key, bool isDown);
	virtual void onKey(int key, bool isDown, bool& shouldCancel);
	virtual bool isFlashMode();
	virtual void onAttack(ActorBase*);
	virtual void onPlayerTick(Player*);
	virtual void onLoadConfig(void* conf);
	virtual void onSaveConfig(void* conf);
	virtual void toggle();
};