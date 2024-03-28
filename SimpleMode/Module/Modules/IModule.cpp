#include "IModule.h"
#include <cstdarg>
#include <iostream>
#include "../../../Utils/Json.hpp"
//void SettingEntry::makeSureTheValueIsAGoodBoiAndTheUserHasntScrewedWithIt() {
//	switch (valueType) {
//	case ValueType::ENUM_T:
//		break;
//	case ValueType::BOOL_T:
//		break;
//	case ValueType::DOUBLE_T:
//		value->_double = std::max(minValue->_double, std::min(maxValue->_double, value->_double));
//		break;
//	case ValueType::FLOAT_T:
//		value->_float = std::max(minValue->_float, std::min(maxValue->_float, value->_float));
//		break;
//	case ValueType::INT_T:
//		value->_int = std::max(minValue->_int, std::min(maxValue->_int, value->_int));
//		break;
//	case ValueType::TEXT_T:
//		//break;
//	default:
//		std::cout << "unrecognized value " << valueType << std::endl;
//		break;
//	}
//}
IModule::IModule(std::string name, int key, Category c, const char* desc) {
	this->keybind = key;
	this->cat = c;
	this->desc = desc;
	//this->registerIntSetting(name, &this->keybind, this->keybind, 0, 0xFF);
	this->registerBoolSetting(name, &this->enabled, false);
	this->ModulePos = Vec2(0.f, 0.f);
}
IModule::~IModule() {
	for (auto it = this->settings.begin(); it != this->settings.end(); it++) {
		delete* it;
	}
	this->settings.clear();
}

void IModule::setEnabled(bool enb) {
	if (this->enabled != enb) {
		this->enabled = enb;

		if (enb)
			this->onEnable();
		else
			this->onDisable();
	}
}

void IModule::toggle() {
	setEnabled(!this->enabled);
}

void IModule::checkEnabled() {
	if (this->enabled != this->prev) {
		if (this->enabled)
			this->onEnable();
		else
			this->onDisable();
		this->prev = this->enabled;
	}
}

std::string IModule::getRawModuleName()
{
	return getModuleName();
}

bool IModule::isEnabled() {
	return this->enabled;
}

bool IModule::isExtended()
{
	return this ->extended;
}

void IModule::registerFloatSetting(std::string name, float* floatPtr, float defaultValue, float minValue, float maxValue) {
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::FLOAT_T;

	setting->value = reinterpret_cast<SettingValue*>(floatPtr);

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_float = defaultValue;
	setting->defaultValue = defaultVal;
	// Min Value
	SettingValue* minVal = new SettingValue();
	minVal->_float = minValue;
	setting->minValue = minVal;

	// Max Value
	SettingValue* maxVal = new SettingValue();
	maxVal->_float = maxValue;
	setting->maxValue = maxVal;

	strcpy_s(setting->name, 19, name.c_str());  // Name

	settings.push_back(setting);  // Add to list
}
void IModule::registerIntSetting(std::string name, int* intPtr, int defaultValue, int minValue, int maxValue)
{
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::INT_T;
	setting->value = reinterpret_cast<SettingValue*>(intPtr);  // Actual Value

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_int = defaultValue;
	setting->defaultValue = defaultVal;

	// Min Value
	SettingValue* minVal = new SettingValue();
	minVal->_int = minValue;
	setting->minValue = minVal;

	// Max Value
	SettingValue* maxVal = new SettingValue();
	maxVal->_int = maxValue;
	setting->maxValue = maxVal;

	// Name
	strcpy_s(setting->name, 19, name.c_str());

	settings.push_back(setting);  // Add to list
}
void IModule::registerEnumSetting(std::string name, SettingEnum* ptr, int defaultValue) {
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::ENUM_T;
	if (defaultValue < 0 || defaultValue >= ptr->GetCount())
		defaultValue = 0;

	// Actual Value
	setting->value = reinterpret_cast<SettingValue*>(&ptr->selected);
	setting->value->_int = defaultValue;

	// Default Value
	SettingValue* defaultVal = new SettingValue();
	defaultVal->_int = defaultValue;
	setting->defaultValue = defaultVal;

	// Min Value (is Extended)
	SettingValue* minVal = new SettingValue();
	minVal->_bool = false;
	setting->minValue = minVal;

	// Enum data
	setting->extraData = ptr;

	strcpy_s(setting->name, 19, name.c_str());
	settings.push_back(setting);
}

void IModule::registerBoolSetting(std::string name, bool* boolPtr, bool defaultValue)
{
	SettingEntry* setting = new SettingEntry();
	setting->valueType = ValueType::BOOL_T;

	setting->value = reinterpret_cast<SettingValue*>(boolPtr);  // Actual value
	SettingValue* defaultVal = new SettingValue();  // Default Value
	defaultVal->_bool = defaultValue;
	setting->defaultValue = defaultVal;
	//v = boolPtr;

//	this->enabled = *boolPtr;
	//defaultVal->Value = *boolPtr;
	strcpy_s(setting->name, 19, name.c_str());  // Name

	settings.push_back(setting);  // Add to list
}

int IModule::getKeybind() {
	return this->keybind;
}

void IModule::setKeybind(int key) {
	this->keybind = key;
}

void IModule::onEnable()
{
}

void IModule::onDisable()
{
}

void IModule::onFrame()
{
}

void IModule::onTick(GameMode*)
{
}

void IModule::onKeyUpdate(int key, bool isDown) {
	if (key == getKeybind()) {
		if (isFlashMode())
			setEnabled(isDown);
		else if (isDown)
			toggle();
	}
}

void IModule::onKey(int key, bool isDown, bool& shouldCancel)
{
}

bool IModule::isFlashMode()
{
	return false;
}

void IModule::onAttack(ActorBase*)
{
}

void IModule::onPlayerTick(Player*)
{
}

void IModule::onLoadConfig(void* conf)
{
}

void IModule::onSaveConfig(void* conf)
{
}

EnumEntry::EnumEntry(const std::string _name, const unsigned char value) {
	name = _name;
	val = value;
}

std::string EnumEntry::GetName() {
	return name;
}

unsigned char EnumEntry::GetValue()
{
	return val;
}

SettingEnum::SettingEnum(std::vector<EnumEntry> entr, IModule* mod) {
	Entrys = entr;
	owner = mod;
	std::sort(Entrys.begin(), Entrys.end(), [](EnumEntry rhs, EnumEntry lhs) {
		return rhs.GetValue() < lhs.GetValue();
		});
}

SettingEnum::SettingEnum(IModule* mod) {
	owner = mod;
}

SettingEnum& SettingEnum::addEntry(EnumEntry entr) {
	auto etr = EnumEntry(entr);
	bool SameVal = false;
	for (auto it = this->Entrys.begin(); it != this->Entrys.end(); it++) {
		SameVal |= it->GetValue() == etr.GetValue();
	}
	if (!SameVal) {
		Entrys.push_back(etr);
		std::sort(Entrys.begin(), Entrys.end(), [](EnumEntry rhs, EnumEntry lhs) {
			return rhs.GetValue() < lhs.GetValue();
			});
	}
	return *this;
}

EnumEntry& SettingEnum::GetEntry(int ind) {
	return Entrys.at(ind);
}

EnumEntry& SettingEnum::GetSelectedEntry() {
	return GetEntry(selected);
}

int SettingEnum::GetCount() {
	return (int)Entrys.size();
}