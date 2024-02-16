#pragma once
#include <Windows.h>
#include <bitset>
#include "ActorList.h"
#include "Item.h"
#include "../Utils/HMath.h"
#include <iostream>
#include <vector>
#include "World.h"
class GameMode;
class Player;
class PlayerLocoMotion;
class Attackedcomponent;
class PlayerAttrib;
class ActorBody;
class GunLogical;
class Seeing;
class BackPack;
class LocalPlayer;
class ActorHorse;

class ActorBase {








};

#pragma pack(push, 4)
class Player :public ActorBase {
private:
	char pad_0x0[0x180]; //0x0
public:
	ActorBody* Actorbody; //0x184
private:
	char pad_0x188[0x98]; //0x21c
public:
	World* world;//0x220
private:
	char pad_0x224[0x34];//224
public:
	PlayerLocoMotion* playerlocomotion; //0x258
	Attackedcomponent* AttackedComponent; //0x25c
private:
	char pad_0x260[0x8];//0x260
public:
	PlayerAttrib* Playerattrib; //0x268
private:
	char pad_0x26c[0xA0]; //0x26C
public:
	double Modelsize; //0x30C
private:
	char pad_0x314[0x4C]; //0x314
public:
	float Diggingprogress; //0x358
private:
	char pad_35c[0x80];// 0x35c
public:
	int OPWay;
private:
	char pad_3E4[0xA8];  //0x3e0
public:
	Vec3i Pos;//0x48c
private:
	char pad_0x498[0x8];  //0x498
public:
	Seeing* seeing; //0x4a0
private:
	char pad_0x4a4[0x98];//0x4a4
public:
	BackPack* Backpack; //0x538
private:
	char pad_53c[0x40]; //0x53c
public:
	int digging;//0x578
	GunLogical* getGunLogical;//0x57c
private:
	char pad_0x57E[0xFE]; //0x57e
public:
	Vec2 grapnelTime;  //0x680
public:
	virtual void ResetSelf(void);
	virtual void Release(void);
	virtual void OnDirty(Player*);
	virtual void ReleaseSelf(void);
	virtual void Init(void);
	virtual __int32 PreTick(void);
	virtual void Tick(void);
	virtual void PostTick(void);
	virtual void validateItems(BackPack*);
	virtual void validateItems(void);
	virtual void validateItemes(void);
	virtual void SerializeToJson(LocalPlayer&);
	virtual void ParseFromJson(void);
	virtual void OnInit(void);
	virtual void OnRelease(void);
	virtual void OnPreTick();
	virtual void OnTick(Player*);
	virtual void OnPostTick(Player*);
	virtual void OnClearNotify(void);
	virtual void OnAddComponent(void);
	virtual void OnRemoveComponent(void);
	virtual void StaticReflexContainer();
	virtual void InitInstance();
	virtual void InitNodeLonely();
	virtual void SetName(std::string);
	virtual void GetTag();
	virtual __int32 SetTag(__int32);
	virtual __int32 SetParent();
	virtual bool SetParent_(void);
	virtual void GetParent();
	virtual void SetParentReflex(void);
	virtual bool CanAttachChild(void);
	virtual int GetChildByName(std::string const&);
	virtual void GetRoot();
	virtual void a_GetRoot(void);
	virtual bool BeginPlay(void);
	virtual bool EndPlay(void);
	virtual void Clone(void);
	virtual void Clones(void);
	virtual void CloneTo(void);
	virtual void onPhysXTouch();
	virtual void onPhysXTouchEnd();
	virtual void OnLoadReflexStart();
	virtual void OnLoadReflexEnd();
	virtual void OnLoadReflexFinish();
	virtual void OnPreSave();
	virtual void NotifyLeaveService();
	virtual void NotifyLeaveServices(void);
	virtual void CanSimulate(void);
	virtual void CanSyncSimulate(void);
	virtual void CheckExclusionReflex(std::string const&);
	virtual void IsInExclusionReflex(std::string const&);
	virtual void updateHeartbeatRent(void);
	virtual void ResourceLoad(void);
	virtual void ResourceUnload(void);
	virtual void ResourceDynamicLoad(void);
	virtual void ResourceDynamicUnload(void);
	virtual void OnResourceFinish();
	virtual void isSupportScriptScope(unsigned __int32 const);
	virtual void CheckResourceLoadCondition();
	virtual void CheckResourceUnoadCondition();
	virtual int OnNameChanged(std::string const&, std::string const&);
	virtual bool CanDelete(void);
	virtual bool CanClone(void);
	virtual void SetEnable(uintptr_t*, bool, bool);
	virtual void SetActive(uintptr_t*, bool, bool);
	virtual bool IsVisible(void);
	virtual bool SetVisible(uintptr_t*, bool);
	virtual bool IsRealVisible();
	virtual bool InheritParentVisible();
	virtual bool IsStreamLoad();
	virtual bool CanActiveGUI();
	virtual bool IsPhysicsSyncAtrr();
	virtual unsigned __int32 IsPhysicsSyncAtrrds(void);
	virtual void HandleInit(void);
	virtual void InitDefaultChildren(void);
	virtual void ProcessRemoteEvent(void);
	virtual void SendEventInvocation(void);
	virtual void SerializeToStream(void);
	virtual void ParseFromStream(void);
	virtual void updateBindChunk(void);
	virtual void InitBoundingBox(void);
	virtual void OnParentChangeAfter(void);
	virtual void OnNodeAttributeChanged(void);
	virtual void OnAddChild(void);
	virtual void OnRemoveChild(void);
	virtual void OnEnterParent(void);
	virtual void OnLeaveParent(void);
	virtual void OnParentChanged(void);
	virtual void OnAncestryChanged(void);
	virtual void OnEnterScene(void);
	virtual void OnLeaveScene(void);
	virtual void OnBeginPlay(Player*);
	virtual void OnEndPlay(Player*);
	virtual void OnActive(void);
	virtual void OnInactive(void);
	virtual void OnNodeLeaveGame(void);
	virtual void OnNodeEnterGame(void);
	virtual void NodeEnterScene(void);
	virtual void NodeLeaveScene(void);
	virtual void BindToScene(void);
	virtual void UnbindFromScene(void);
	virtual void DescendantNodeEnter(void);
	virtual void DescendantNodeLeave(void);
	virtual void OnDescendantNodeEnter(void);
	virtual void OnDescendantNodeLeave(void);
	virtual void OnLuaIndex(uintptr_t*, std::string const&);
	virtual void OnLuaNewIndex(uintptr_t*, std::string const&, int);
	virtual void BindNodeID(void);
	virtual void UnbindNodeID(void);
	virtual void getObjId(Player*);
	virtual void SetParentCommon(void);
	virtual void tick(LocalPlayer*);
	virtual void update(LocalPlayer*, float);
	virtual void castShadow(Player*);
	virtual void enterWorld(LocalPlayer*, World*);
	virtual void leaveWorld(Player*, bool);
	virtual void updateViewPos(LocalPlayer const&);
	virtual void save(void);
	virtual void saveToNet(void);
	virtual void takeAccountItemsToHost(LocalPlayer*, int, int);
	virtual void voidblockTick(World*, Vec3 const&);
	virtual void loadFromNet(void const*, int);
	virtual void validServerBackPackLog(BackPack*);
	virtual void onAfterTick(void);
	virtual void checkNeedClear(void);
	virtual void onCollideWithPlayer(Player*);
	virtual void collideWithActor(Player*);
	virtual void onCollideWithActor(Player*);
	virtual void applyActorCollision(Player*);
	virtual void applyActorElasticCollision(Player*);
	virtual void applyActorObstructCollision(Player*);
	virtual void setRotaionLimitAngle(LocalPlayer*, float);
	virtual void getRotaionLimitAngle(LocalPlayer*);
	virtual void updateHeartbeatRents(void);
	virtual void needCheckVisible(void);
	virtual void updateHeartbeatRentss(void);
	virtual void newActorBody(void);
	virtual void updateHeartbeatRentsss(void);
	virtual void a_newActorBody(void);
	virtual void canBeCollidedWith(PlayerAttrib*);
	virtual void validServerBackPackLogs(BackPack*);
	virtual void attackedFrom(Attackedcomponent*, ActorPlayerList*);
	virtual void updateHeartbeatRent_s();
	virtual bool canBePushed(Player*);
	virtual void a_validateItems(BackPack*);
	virtual void moveToPosition(LocalPlayer, Vec3 const*, Vec4*, int);
	virtual void moveToPosition(PlayerAttrib, Vec3 const*, Vec2, int);
	virtual void syncFullyCustomModelData(World*, Player*);
	virtual void _updateHeartbeatRent();
	virtual void s_updateHeartbeatRent();
	virtual void syncAttr(LocalPlayer*, int, int);
	virtual void getUIModelViewScale(void);
	virtual bool interact(Player*, Player*, bool, bool);
	virtual int getTextureType(Block*);
	virtual void validServerBackPackLog_(BackPack*);
	virtual int getTextureType_(Block*);
	virtual int getTextureType_s(Block*);
	virtual void updateHeartbeatRent_t();
	virtual int GetPathHideRange(Player*);
	virtual void saveCSPermitData();
	virtual void validServerBackPackLog_t();
	virtual void updateBodyByFullyCustomModel(LocalPlayer*);
	virtual void updateBodyByImportModel(LocalPlayer*);
	virtual void getViewBox(Vec3*);
	virtual void getObjType(Item*);
	virtual bool canAttackByItemSkill(Player*, int, Player*);
	virtual void resetRound(void);
	virtual void c_validateItems(BackPack*);
	virtual void addHPEffect(PlayerAttrib*);
	virtual void addHPEffect_(PlayerAttrib*);
	virtual void changeBaseModel(void);
	virtual void updateViewPos_b(void);
	virtual void getAnimBodyId(PlayerAttrib*);
	virtual void validServerBackPackLog_a();
	virtual void validServerBackPackLog_b();
	virtual void validServerBackPackLog_c();
	virtual __int32 getActorType(void*);
	virtual void newActorBody_a(void);
	virtual void updateBlockLaser(void);
	virtual void supportSaveToPB(void);
	virtual void saveToPB(void);
	virtual void LoadFromPB(void);
	virtual bool isSleeping();
	virtual bool isRestInBed();
	virtual bool teleportMap(int);
	virtual bool isInvulnerable(int);
	virtual bool isDead(void);
	virtual void setPosition(Vec3i);    //ÉèÖÃ×ø±ê
	virtual void getEyePosition(void);
	virtual void getChestPosition(void);
	virtual __int32 getViewDist(void);
	virtual void updateViewPos_a(void);
	virtual float getVerticalFaceSpeed();
	virtual __int32 getChestHeight(void);
	virtual void setScale(float);
	virtual float getScale(void);
	virtual void updateScale(void);
	virtual void	setCustomScale(float);
	virtual void	getCustomScale(void);
	virtual void	getObjType(void);
	virtual bool isBurning(void);
	virtual int getEyeHeight(void);
	virtual void playAnim(int, bool, int);
	virtual bool playAnimById(int);
	virtual void resetAllFlags(unsigned int);
	virtual void setFlagBit(int, bool);
	virtual bool getFlying(void);
	virtual void setFaceYaw(float, bool);
	virtual void tryMoveToActor(int, bool);
	virtual void tryMoveToActor(int, float);
	virtual void tryMoveToPos(Vec3i, float);
	virtual void tryMoveTo(Vec3i, float, bool, bool, bool);
	virtual void newActorBody_d();
	virtual int getMass(void);
	virtual void setMotionChange(Vec3*, bool, bool);
	virtual void getBodySize(float*, float*);
	virtual bool playActForTrigger(int);
	virtual void newActorBody_e();
	virtual void showNickName(bool);
	virtual void setNickName(char*);
	virtual void setFallGround(bool);
	virtual bool getFallGround(void);
	virtual void newActorBody_f();
	virtual bool canControl(void);
	virtual void setCanControl(bool);
	virtual void newActorBody_g();
	virtual void playEffect(unsigned int);
	virtual void validServerBackPackLog_d(void);
	virtual void updateViewPos_c(void);
	virtual void updateHeartbeatRent_a(void);
	virtual void SetBindChunk(bool);
	virtual bool getUsingEmitter(void);
	virtual void setBodyCull(void);
	virtual bool skillPlayAnim(int, int, int, int);
	virtual bool skillStopAnim(int, int, bool);
	virtual bool skillStopToolAnim(int);
	virtual bool skillPlayBodyEffect(void);
	virtual bool skillStopBodyEffect(char const*);
	virtual void gmDrawWrapBox(void);
	virtual void getsyncData(void);
	virtual void setsyncData(void);
	virtual void validServerBackPackLog_e(void);
	virtual void updateViewPos_d(void);
	virtual void setMonsterId(int);
	virtual void validServerBackPackLog_f(void);
	virtual void newActorBody_h(void);
	virtual void updateViewPos_e(void);
	virtual void validServerBackPackLog_g(void);
	virtual void updateViewPos_f(void);
	virtual void updateViewPos_g(void);
	virtual void validateItems_a(void);
	virtual void getActorInPortal(void);
	virtual void getActorBindVehicle(void);
	virtual void getBindActorCom(void);
	virtual void getUpdateFrequencyCom(void);
	virtual void GetGameObject(void);
	virtual void GetTransform(void);
	virtual bool updateHeartbeatRent_b(void);
	virtual void validateItems_b(void);
	virtual void isInvisible(void);
	virtual void setHPProgressDirty(void);
	virtual void setMoveForward(float);
	virtual void setMoveStrafing(float);
	virtual void updateViewPos_h(void);
	virtual void walkForward(int, int);
	virtual void walkStrafing(int, int);
	virtual void walkUp(void);
	virtual void walkUp_a(void);
	virtual void livingHPtick(void);
	virtual void mobHPTick(void);
	virtual void getHPProgressComponent(void);
	virtual int getStepHeight(void);
	virtual int playHurtSound(void);
	virtual int playmobHurtSound(void);
	virtual int playStepSound(void);
	virtual int playClimbStepSound(void);
	virtual float getSoundVolume(void);
	virtual float getSoundPitch(void);
	virtual float onBuffChange(int, int, int, int, int);
	virtual void setFire(Vec3i, __int32);
	virtual void newActorBody_i(void);
	virtual char canAttack(void);
	virtual bool attackActor(ActorPlayerList*, int, int);
	virtual void a_playAnim(int, bool, int);
	virtual void stopAnim(int, bool);
	virtual int getOxygenUseInterval(void);
	virtual float getOxygenUseRate(void);
	virtual void doActualItemSkillAttack(ActorPlayerList*, unsigned int, int);
	virtual void setRidingActor(Player*);
	virtual void doActualAttack(ActorList*, int);
	virtual void doActualRangeAttack(Player*);
	virtual float getUIModelViewScale_a(void);
	virtual bool ComboAttackStateRunning(void);
	virtual bool init(int, char const*, int, char const*);
	virtual bool initAvatar(void);
	virtual void initCusMotion(void);
	virtual void replacePlayer(Vec3);
	virtual bool mountActor(Player*, bool, int);
	virtual bool carryActor(Player*, Vec3);
	virtual void renderUI(void);
	virtual void onSetCurShortcut(int);
	virtual void onDie(void);
	virtual void addAchievement(int, unsigned int, int, int);
	virtual void addOWScore(float);
	virtual void checkNewbieWorldProgress(int, int);
	virtual void checkNewbieWorldProgress(int, char const*);
	virtual void checkNewbieWorldTask(int);
	virtual void a_updateHeartbeatRent(void);
	virtual void checkCollideOnTrigger(Player*);
	virtual bool interactActor(Player*, bool);
	virtual bool performInteractActor(Player*, int, bool, bool);
	virtual int interactBlock(int*, int, float);
	virtual bool recoverBlock(Vec3 const&, unsigned int, int);
	virtual bool farmOpenBlock(Vec3 const&, unsigned int, int);
	virtual bool interactHorse(ActorHorse*, bool);
	virtual int useItemSkill(void);
	virtual bool doSpecialSkill(void);
	virtual void showSpecailTryShapeAnim(void);
	virtual void hideSpecailTryShapeAnim(void);
	virtual void getCatchBall(void);
	virtual void doThrowGravityActor(int, float, ActorPlayerList*);
	virtual bool doCatchGravityActor(ActorPlayerList*, int, int);
	virtual void getCatchGravityActor(void);
	virtual void beginChargeThrowGravityActor(void);
	virtual void doPutGravityActor(ActorPlayerList*);
	virtual bool attackRangedFree(int);
	virtual bool SheildDefence(int, int);
	virtual bool openPlotDialogue(ActorBase*, int, Vec3, int);
	virtual bool execCmd(char const*);
	virtual void setVipInfo(uintptr_t const&);
	virtual void setVipInfo(void);
	virtual void setGVoiceInfo(int);
	virtual void tickOperate(void);
	virtual void onOperateEnded(void);
	virtual void onPickupItem(ActorPlayerList*);
	virtual void calFallMotion(float, bool);
	virtual void tryStandup(float, bool);
	virtual bool saveToFile(int, uintptr_t);
	virtual void applyEquips(int, uintptr_t);
	virtual void onDisApplyEquips(int);
	virtual void onDisApplyEquips(int, int, int, int);
	virtual void onApplyEquips(int, int);
	virtual void doGunFire(int);
	virtual void doReload(int, int);
	virtual void beHurtOnTrigger(float);
	virtual void moveOneBlockSizeOnTrigger(void);
	virtual bool revive(int, int, int, int);
	virtual bool useItem(int, int, bool, unsigned int);
	virtual bool usePackingFCMItem(int, Vec3);
	virtual bool getAimPos(int&, int&, int&, int&, bool);
	virtual Vec3 getCameraLookDir(void);
	virtual bool setJumping(bool);
	virtual int gainItems(Vec3i, bool);
	virtual int gainItemsByIndex(Vec3i, bool);
	virtual int gainItemsUserdata(int, int, char const*, int);
	virtual int gainItemsByGrid(BackPack const*, int);
	virtual int exchangeItems(int, int, int, int);
	virtual void jumpOnce(void);
	virtual void postInfoTips(int);
	virtual void setAccumulatorState(float);
	virtual void sortPack(int);
	virtual void sortStorageBox(void);
	virtual int enchant(int, int, int* const);
	virtual int enchantRandom(int);
	virtual int canEnchant(int, int, int* const);
	virtual int calcEnchantCost(int, int* const);
	virtual void setUserDataStr(int, std::string);
	virtual void writeLetters(int, std::string);
	virtual void writeBlueprint(int, std::string);
	virtual void writeInstruction(int, std::string);
	virtual int repair(Vec3i);
	virtual bool canRepair(Vec3i);
	virtual int calcRepairCost(Vec3i);
	virtual int NewRepair(Vec3i, Vec3i);
	virtual void changePlayerModel(int, int, char const*, char const*, int, int, bool);
	virtual void setCustomModelForActorBody(int, int, char const*, char const*, ActorBody*);
	virtual void getFullyCustomModelKey(void);
	virtual bool useSpecialItem(Vec3i);
	virtual void npcTrade(int, int, bool, int);
	virtual void starConvert(int);
	virtual void playBlockPlaceSound(Vec3i, int);
	virtual void playBlockDigSound(Vec3i, int);
	virtual char placeBlock(bool, Vec3i, unsigned int, DWORD, DWORD, int, int, int, DWORD, DWORD);     //1\xyz\1
	virtual void summonAccountHorse(int);
	virtual void accountHorseEgg(void);
	virtual void avatarSummon(int);
	virtual void setSpectatorMode(unsigned int);
	virtual void setSpectatorType(unsigned int);
	virtual void getOPWay(void);
	virtual void setOPWay(int);
	virtual void changeOPWay(void);
	virtual void getCurWorldMapId(void);
	virtual void newAdNpcAddExp(int, int);
	virtual void tryBuyAdNpcGood(int, int);
	virtual void onBuyAdNpcGood(int, int);
	virtual void AddStar(int);
	virtual void completeTask(int);
	virtual void playAct(int);
	virtual void stopAct(void);
	virtual int closeEditActorModel(int, std::string);
	virtual int closeFullyCustomModelUI(int, std::string, std::string);
	virtual bool isShapeShift(void);
	virtual int getSkinID(void);
	virtual int summonPet(int, std::string, Vec3i, std::string);
	virtual void syncUseItemByHomeLand(int, int);
	virtual void setApiid(int);
	virtual int getApiid(void);
	virtual void setLang(int);
	virtual int getLang(void);
	virtual void setEnterTs(int);
	virtual int getEnterTs(void);
	virtual int UploadCheckInfo2Host(int, std::string const&);
	virtual void GetAdShopExtraItemReward(int, int, int);
	virtual void ExtraStoreItem(int, int, int);
	virtual int getSkinActPlayerNum(void);
	virtual int getSkinActPlayerUinByIndex(int);
	virtual int scanSkinActActorList(void);
	virtual bool playSkinAct(int, int, int);
	virtual void sendActorInvite(int, int, int);
	virtual void onAnimInterrupt(void);
	virtual bool checkCanPlaySkinAct(void);
	virtual bool checkHasEnoughSpace2SkinAct(int);
	virtual bool checkNearEnough2SkinAct(int);
	virtual bool checkIsDivByBlock(Vec2);
	virtual bool checkIsDivideByBlock(int);
	virtual World getSkinActTargetPos(int);
	virtual void addDirtyIndex(int);
	virtual void doPickActorByItemSkill(int, Vec3i, Vec3&, Vec3&);
	virtual void doPickBlockByItemSkill(int, Vec3&, Vec3&);
	virtual void doPickPhysicsActorByItemSkill(int, Vec3i, Vec3&, Vec3&);
	virtual void setHookObj(int, bool);
	virtual void setContainersPassword(World const&, int);
	virtual void setJumpState(int);
	virtual void setStopState(bool);
	virtual void setCurrentMoveState(bool);
	virtual void updateRunState(void);
	virtual void getCarryingBindPos(void);
	virtual void SetTreeItemIndex(int, int);
	virtual void randomSelect(std::vector<PlayerAttrib const&>, int);
	virtual void onMoveTick(void);
	virtual bool openContainer(uintptr_t);
	virtual bool openContainer(World);
	virtual void closeContainer(void);
	virtual bool validServerBackPackLog(void);
	virtual void destroyBlock(Vec3i, int, bool, bool);
	virtual bool disMountEmitter(Vec3i const&);
	virtual bool disMountEmitterClient(Vec3i const&);
	virtual bool mountEmitter(Vec3i const&);
	virtual bool operateManualEmitter(Vec3i const&);
	virtual bool operateManualEmitterClient(Vec3i const&);
	virtual void fall(float);
	virtual float getFallHurtSubtract(void);
	virtual void canPlayStepSound(void);
	virtual void canPlayHurtSound(void);
	virtual void getOpenContainerCom(void);
	virtual void getItemSkillComponent(void);
	virtual void changeMoveFlag(unsigned int, bool);
	virtual void onSetCurSprayPaint(bool);
	virtual void a_validServerBackPackLog(void);
	virtual void resetEyeDir(bool);
	virtual void tryMountActor(ActorList*, int);
	virtual void shapeShift(void);
	virtual void tryWakeup(void);
	virtual void switchCurrentItem(void);
	virtual int onInputEvent(std::string const&);
	virtual void tryShapeShift(int);
	virtual void trySleep(int);
	virtual void setViewMode(int, bool);
	virtual void setCurShortcut(int);
	virtual void setCurSprayPaint(bool);
	virtual int doPick(bool, bool, bool);
	virtual void changeGameMode(bool);
	virtual void doExchangeItems(int, int, int, int, int);
	virtual int lootItem(int, int);
	virtual void swapItem(int, int);
	virtual void mergeItem(int, int);
	virtual void discardItem(int, int);
	virtual void craftItem(int, int);
	virtual void setItem(Vec3i, char const&);
	virtual void setItemWithoutLimit(Vec3i, char const&, char const&);
	virtual void moveItem(Vec3i);
	virtual bool takeAccountItemsToHost(int, int);
	virtual void switchSkinActView(void);
	virtual void tryCarryActor(ActorList*, Vec3i);
	virtual void setRefreshType(int);
	virtual void SendActionLog2Host(bool, std::string const&, std::string const&);
	virtual bool syncFullyCustomModelData(ActorPlayerList*);
	virtual void getScene(void);
	virtual void onMoveUp(int);



};
#pragma pack(pop)
class Attackedcomponent :public ActorBase {
};
class BackPackGrid :public Player {
};

class LocalPlayer :public Player {
private:

};

class PlayerLocoMotion : public Player {
private:
	char pad_0x90[0x90];//0x90
public:
	int JumpTime; //0x94
	int button; //0x98
private:
	char pad_0x9C[0x8];      //0x9C
public:
	int onGround;  //0xA4
private:
	char pad_0x34[0x34]; //0xa8
public:
	Vec3 xyzPos; //0xDC
private:
	char pad_0xE4[0x4C]; //0xE4
public:
	Vec3 velocity; //0xDC
};
class PlayerAttrib :public Player {
private:
	char pad_C8[0xC8]; //0xC8
public:
	float Movespeed; //0xCC
	float Runningspeed; //0xD0
	float Squatspeed; //0xD4
	float Speedwater; //0xD8
	float Jumpheight; //0xdc
};
class ActorBody :public Player {
};
class GunLogical :Player {
private:
	char pad_0x0[0xC];//0x0
public:
	int bullet;//0xc
	float spread;//0x10
};
class Seeing:Player{
public:
	uint32_t NpcID; //0x0
private:
	char pad_0x4[0x248];//0x4
public:
	int playerID; //0x248
};
class 	BackPack :public BackPackGrid {
};
