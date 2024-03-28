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
class Attackedcomponent;
class LocalPlayer;
class ActorHorse;

#pragma pack(push, 4)
class PlayerLocoMotion {
private:
	char pad_0x90[0x90];//0x90
public:
	int JumpTime; //0x94
	int button; //0x98
private:
	char pad_0x9C[0x8];      //0x9C
public:
	bool onGround;  //0xA4
private:
	char pad_0x34[0x38]; //0xA4
public:
	Vec3i xyzPos; //0xDC
private:
	char pad_0xE4[0x4C]; //0xE4
public:
	Vec3 velocity; //0xDC
};
class PlayerAttrib {
private:
	char pad_C8[0xC8]; //0xC8
public:
	float Movespeed; //0xCC
	float Runningspeed; //0xD0
	float Squatspeed; //0xD4
	float Speedwater; //0xD8
	float Jumpheight; //0xdc
};
class ActorBody {
private:
	char pad_0x0[0x4C];
public:
	float angle;
	float trueangle;  //54
private:
	char pad_0x54[0x27C];
public:
	double Lockangle;
};
class GunLogical {
private:
	char pad_0x0[0xC];//0x0
public:
	int bullet;//0xc
	float spread;//0x10
};
class Seeing {
public:
	uint32_t NpcID; //0x0
private:
	char pad_0x4[0x248];//0x4
public:
	int playerID; //0x248
};
class 	BackPack {
};
#pragma pack(pop)

#pragma pack(push, 4)
class ActorBase {
private:
	char pad_0x0[0x54]; //0x0
public:
	int isplayer; //0x58
private:
	char pad_0x58[0x128];
public:
	ActorBody* Actorbody; //0x184
private:
	char pad_0x188[0xDC]; //0x21c
public:
	World* world;//0x260
private:
	char pad_0x224[0x34];//264
public:
	PlayerLocoMotion *playerlocomotion; //0x298
	Attackedcomponent *AttackedComponent; //0x29c
private:
	char pad_0x260[0x8];//0x2A0
public:
	PlayerAttrib *Playerattrib; //0x2A8
private:
	char pad_0x26c[0xA0]; //0x2Ac
public:
	double Modelsize; //0x34C
private:
	char pad_0x314[0x48]; //0x350
public:
	float Diggingprogress; //0x398
private:
	char pad_35c[0x80];// 0x35c
public:
	int OPWay;  
private:
	char pad_3E4[0xA8];  //0x3e0
public:
	Vec3 Pos;//0x48c
private:
	char pad_0x498[0x8];  //0x498
public:
	Seeing *seeing; //0x4a0
private:
	char pad_0x4a4[0x98];//0x4a4
public:
	BackPack *Backpack; //0x538
	std::string Name;  //53c
private:
	char pad_53c[0x3C]; //0x540
public:
	int digging;//0x578
	GunLogical *getGunLogical;//0x57c
private:
	char pad_0x57E[0xFE]; //0x57e
public:
	Vec2 grapnelTime;  //0x680
public:
	virtual void GetRTTI(void);
	virtual void sub_1143BC70(void);
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
	virtual void SerializeToJson(LocalPlayer&);
	virtual void ParseFromJson(void);
	virtual void _Release(void);
	virtual void OnRelease(void);
	virtual void OnPreTick(void);
	virtual void OnTick(Player*);
	virtual void OnPostTick(Player*);
	virtual void OnClearNotify(void);
	virtual void OnAddComponent(void);
	virtual void OnRemoveComponent(void);
	virtual void StaticReflexContainer();
	virtual void InitInstance(void);
	virtual void InitNodeLonely(void);
	virtual void SetName(std::string);
	virtual void GetTag(void);
	virtual __int32 SetTag(__int32);
	virtual __int32 SetParent(uintptr_t*);
	virtual bool SetParent_(void);    //30
	virtual void GetParent(void);
	virtual void SetParentReflex(void);
	virtual bool CanAttachChild(void);
	virtual __int32 GetChildByName(std::string const&);
	virtual void GetRoot(void);
	virtual void _GetRoot(void);
	virtual bool BeginPlay(void);
	virtual bool EndPlay(void);
	virtual void Clone(void);
	virtual void Clones(void);
	virtual void CloneTo(void);
	virtual void onPhysXTouch(void);
	virtual void OnUnbindGameObject(void);  //43
	virtual void OnLoadReflexStart(void); //44
	virtual void OnLoadReflexEnd(void); //45
	virtual void OnLoadReflexFinish(void);   //46
	virtual bool OnPreSave(void); //47
	virtual void NotifyEnterService(void*); //48
	virtual void NotifyLeaveService(void*); //49
	virtual void CanSimulate(void);    //50
	virtual void CanSyncSimulate(void);    //51
	virtual void CheckExclusionReflex(std::string const&);
	virtual void IsInExclusionReflex(std::string const&);
	virtual void updateHeartbeatRent(void);
	virtual void ResourceLoad(void);   //60
	virtual void ResourceUnload(void);
	virtual void ResourceDynamicLoad(void);
	virtual void ResourceDynamicUnload(void);
	virtual void OnResourceFinish();
	virtual void isSupportScriptScope(unsigned __int32 const);
	virtual void CheckResourceLoadCondition();
	virtual void CheckResourceUnoadCondition();
	virtual __int32 OnNameChanged(std::string const&, std::string const&);
	virtual bool CanDelete(void);
	virtual bool CanClone(void);
	virtual void SetEnable(uintptr_t*, bool, bool);
	virtual void SetActive(uintptr_t*, bool, bool);
	virtual bool IsVisible(void);
	virtual bool SetVisible(uintptr_t*, bool);
	virtual bool IsRealVisible();
	virtual bool InheritParentVisible();  //70
	virtual bool IsStreamLoad(void);
	virtual bool CanActiveGUI(void);
	virtual bool IsPhysicsSyncAtrr();
	virtual __int32 IsPhysicsSyncAtrrds(void);
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
	virtual void OnRemoveChild(void);  //85
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
	virtual void BindToScene(void);   //100
	virtual void UnbindFromScene(void);
	virtual void DescendantNodeEnter(void);
	virtual void DescendantNodeLeave(void);
	virtual void OnDescendantNodeEnter(void);
	virtual void OnDescendantNodeLeave(void);
	virtual void OnLuaIndex(uintptr_t*, std::string const&);
	virtual void OnLuaNewIndex(uintptr_t*, std::string const&, __int32);
	virtual void BindNodeID(void);
	virtual void UnbindNodeID(void);
	virtual void getObjId(Player*);
	virtual void SetParentCommon(void);
	virtual void tick(LocalPlayer*);
	virtual void update(LocalPlayer*, float);
	virtual void castShadow(Player*);
	virtual void enterWorld(LocalPlayer*, World*);
	virtual void leaveWorld(bool);
	virtual void updateViewPos(LocalPlayer const&);
	virtual void save(void);
	virtual void saveToNet(void);
	virtual void takeAccountItemsToHost(LocalPlayer*, __int32, __int32);
	virtual void voidblockTick(World*, Vec3 const&);
	virtual void loadFromNet(void const*, __int32);
	virtual void validServerBackPackLog(BackPack*);
	virtual void onAfterTick(void);
	virtual void checkNeedClear(void);
	virtual void onCollideWithPlayer(Player*);
	virtual void collideWithActor(Player*);
	virtual void onCollideWithActor(Player*);
	virtual void applyActorCollision(Player*);
	virtual void applyActorElasticCollision(Player*);   //130
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
	virtual void moveToPosition(Vec3 const*, Vec4*, __int32);
	virtual void moveToPosition(Vec3 const*, Vec2, __int32);
	virtual void syncFullyCustomModelData(World*, Player*);
	virtual void _updateHeartbeatRent();
	virtual void s_updateHeartbeatRent();
	virtual void syncAttr(LocalPlayer*, __int32, __int32);
	virtual void getUIModelViewScale(void);
	virtual bool interact(Player*, Player*, bool, bool);
	virtual __int32 getTextureType(Block*);
	virtual void validServerBackPackLog_(BackPack*);
	virtual __int32 getTextureType_(Block*);
	virtual __int32 getTextureType_s(Block*);
	virtual void updateHeartbeatRent_t();
	virtual __int32 GetPathHideRange(Player*);
	virtual void saveCSPermitData();  //160
	virtual void validServerBackPackLog_t();
	virtual void updateBodyByFullyCustomModel(LocalPlayer*);
	virtual void updateBodyByImportModel(LocalPlayer*);
	virtual void getViewBox(Vec3*);
	virtual void getObjType(Item*);
	virtual bool canAttackByItemSkill(Player*, __int32, Player*);
	virtual void resetRound(void);
	virtual void c_validateItems(BackPack*);
	virtual void addHPEffect(PlayerAttrib*);
	virtual void addHPEffect_(PlayerAttrib*);
	virtual void changeBaseModel(void);
	virtual void updateViewPos_b(void);
	virtual void getAnimBodyId(PlayerAttrib*);
	virtual __int32 getActorType(void*);
	virtual void updateBlockLaser(void);
	virtual void supportSaveToPB(void);
	virtual void saveToPB(void);
	virtual void LoadFromPB(void);
	virtual bool isSleeping();
	virtual bool isRestInBed();
	virtual bool teleportMap(__int32);
	virtual bool isInvulnerable(__int32);
	virtual bool isDead(void);
	virtual void setPosition(Vec3i);    //ÉèÖÃ×ø±ê
	virtual void getEyePosition(void);
	virtual void getChestPosition(void);  //190
	virtual __int32 getViewDist(void);
	virtual void updateViewPos_a(void);
	virtual float getVerticalFaceSpeed();
	virtual __int32 getChestHeight(void);
	virtual void setScale(float);
	virtual float getScale(void);
	virtual void updateScale(void);
	virtual void	setCustomScale(float);
	virtual void	getCustomScale(void);
	virtual void sub_000000(void);
	virtual void	getObjType(void);   //200
	virtual bool isBurning(void);
	virtual __int32 getEyeHeight(void);
	virtual void playAnim(__int32, bool, __int32);
	virtual bool playAnimById(__int32);
	virtual void resetAllFlags(unsigned __int32);
	virtual void setFlagBit(__int32, bool);
	virtual void setSneaking(bool);
	virtual bool setFlying(bool);
	virtual void setRun(bool);
	virtual bool getFlying(void);    //210
	virtual void setFaceYaw(float, bool);
	virtual void tryMoveToActor(__int32, bool);
	virtual void tryMoveToPos(Vec3i, float);
	virtual void tryMoveTo(Vec3i, float, bool, bool, bool);
	virtual void newActorBody_d();
	virtual __int32 getMass(void);
	virtual void setMotionChange(Vec3*, bool, bool);
	virtual void getBodySize(float*, float*);
	virtual bool playActForTrigger(__int32);
	virtual void newActorBody_e();
	virtual void showNickName(bool);
	virtual void setNickName(char*);
	virtual void setFallGround(bool);
	virtual bool getFallGround(void);
	virtual void newActorBody_f();
	virtual bool canControl(void);
	virtual void setCanControl(bool);
	virtual void newActorBody_g();
	virtual void playEffect(unsigned __int32);
	virtual void stopEffect(unsigned __int32);  //230
	virtual void validServerBackPackLog_d(void);
	virtual void updateViewPos_c(void);
	virtual void updateHeartbeatRent_a(void);
	virtual void SetBindChunk(bool);
	virtual bool getUsingEmitter(void);
	virtual void setBodyCull(void);
	virtual bool skillPlayAnim(__int32, __int32, __int32, __int32);
	virtual bool skillStopAnim(__int32, __int32, bool);
	virtual bool skillStopToolAnim(__int32);
	virtual void skillStopToolAnim_a(__int32);
	virtual bool skillPlayBodyEffect(void);
	virtual bool skillStopBodyEffect(char const*);
	virtual void gmDrawWrapBox(void);    //  243
	virtual void getsyncData(void);
	virtual void setsyncData(void);
	virtual void validServerBackPackLog_e(void);
	virtual void updateViewPos_d(void);
	virtual void setMonsterId(__int32);
	virtual void validServerBackPackLog_f(void);
	virtual void newActorBody_h(void);
	virtual void updateViewPos_e(void);
	virtual void validServerBackPackLog_g(void);
	virtual void updateViewPos_f(void);
	virtual void updateViewPos_g(void);
	virtual void validateItems_a(void);
	virtual void validateItems_as(void);
	virtual void validateItems_aa(void);
	virtual void validateItems_ag(void);
	virtual void getActorInPortal(void);
	virtual void getActorBindVehicle(void);
	virtual void getBindActorCom(void);
	virtual void getUpdateFrequencyCom(void);
	virtual void GetGameObject(void);  //260
	virtual void GetTransform(void);
	virtual bool updateHeartbeatRent_b(void);
	virtual void validateItems_b(void);
	virtual void isInvisible(void);
	virtual void setHPProgressDirty(void);
	virtual void setMoveForward(float);
	virtual void setMoveStrafing(float);
	virtual void updateViewPos_h(void);
	virtual void walkForward(__int32, __int32);
	virtual void walkStrafing(__int32, __int32);
	virtual void walkUp(__int32, __int32);
	virtual void walkUp_a(__int32, __int32);
	virtual void livingHPtick(void);
	virtual void mobHPTick(void);
	virtual void getHPProgressComponent(void);
	virtual __int32 getStepHeight(void);
	virtual __int32 playHurtSound(void);
	virtual __int32 _playHurtSound(void);
	virtual __int32 playStepSound(void);//282
	virtual __int32 playClimbStepSound(void);
	virtual float getSoundVolume(void);
	virtual float getSoundPitch(void);
	virtual float onBuffChange(__int32, __int32, __int32, __int32, __int32);
	virtual void setFire(Vec3i, __int32);
	virtual void _newActorBody(void);
	virtual char canAttack(void);   //488
	virtual bool attackActor(ActorPlayerList*, __int32, __int32);
	virtual void a_playAnim(__int32, bool, __int32);
	virtual void stopAnim(__int32, bool);
	virtual __int32 getOxygenUseInterval(void);//290
	virtual float getOxygenUseRate(void);
	virtual void doActualItemSkillAttack(ActorPlayerList*, unsigned __int32, __int32);
	virtual void setRidingActor(Player*);
	virtual void doActualAttack(ActorBase*, __int32);
	virtual void doActualRangeAttack(Player*);
	virtual float getUIModelViewScale_a(void);
	virtual void getAttackingTargetComponent(void);
	virtual bool ComboAttackStateRunning(void);
	virtual bool init(__int32, char const*, __int32, char const*);
	virtual bool initAvatar(void);//300
	virtual void initCusMotion(void);
	virtual void replacePlayer(Vec3);
	virtual bool mountActor(Player*, bool, __int32);
	virtual bool carryActor(Player*, Vec3);
	virtual void renderUI(void);
	virtual void onSetCurShortcut(__int32);
	virtual void onDie(void);
	virtual void addAchievement(__int32, unsigned __int32, __int32, __int32);
	virtual void addOWScore(float);
	virtual void checkNewbieWorldProgress(__int32, __int32);
	virtual void checkNewbieWorldProgress(__int32, char const*);
	virtual void checkNewbieWorldTask(__int32);
	virtual void a_updateHeartbeatRent(void);
	virtual void checkCollideOnTrigger(Player*);
	virtual bool interactActor(ActorBase*, __int32, bool);
	virtual bool performInteractActor(Player*, __int32, bool, bool);
	virtual __int32 interactBlock(__int32*, __int32, float);
	virtual bool recoverBlock(Vec3 const&, unsigned __int32, __int32);
	virtual bool farmOpenBlock(Vec3 const&, unsigned __int32, __int32);
	virtual bool interactHorse(ActorHorse*, bool);
	virtual __int32 useItemSkill(void);
	virtual bool doSpecialSkill(void);
	virtual void showSpecailTryShapeAnim(void);
	virtual void hideSpecailTryShapeAnim(void);
	virtual void getCatchBall(void);
	virtual void doThrowGravityActor(__int32, float, ActorPlayerList*);
	virtual bool doCatchGravityActor(ActorPlayerList*, __int32, __int32);
	virtual void getCatchGravityActor(void);
	virtual void beginChargeThrowGravityActor(void);
	virtual void doPutGravityActor(ActorPlayerList*);//330
	virtual bool attackRangedFree(__int32);
	virtual void attackCharge(__int32);
	virtual bool SheildDefence(__int32, __int32);
	virtual bool openPlotDialogue(ActorBase*, __int32, Vec3, __int32);
	virtual void closePlotDialogue(void);
	virtual bool execCmd(char const*);
	virtual void setVipInfo(uintptr_t const&);
	virtual void setVipInfo(void);
	virtual void setGVoiceInfo(__int32);
	virtual void tickOperate(void);
	virtual void onOperateEnded(void);
	virtual void onPickupItem(ActorPlayerList*);
	virtual void calFallMotion(float, bool);
	virtual void tryStandup(float, bool);
	virtual bool saveToFile(__int32, uintptr_t);
	virtual void applyEquips(__int32, uintptr_t);
	virtual void onDisApplyEquips(__int32);
	virtual void onDisApplyEquips(__int32, __int32, __int32, __int32);
	virtual void onApplyEquips(__int32, __int32);
	virtual void doGunFire(__int32);  //350
	virtual void doReload(__int32, __int32);
	virtual void beHurtOnTrigger(float);
	virtual void moveOneBlockSizeOnTrigger(void);
	virtual bool revive(__int32, Vec3i);
	virtual bool useItem(__int32, __int32, bool, unsigned __int32);
	virtual bool usePackingFCMItem(__int32, Vec3);
	virtual bool getAimPos(__int32&, __int32&, __int32&, __int32&, bool);
	virtual Vec3 getCameraLookDir(void);
	virtual bool setJumping(bool);
	virtual __int32 gainItems(Vec3i, bool);  //360
	virtual __int32 gainItemsByIndex(Vec3i, bool);
	virtual __int32 gainItemsUserdata(__int32, __int32, char const*, __int32);
	virtual __int32 gainItemsByGrid(BackPack const*, __int32);
	virtual __int32 exchangeItems(__int32, __int32, __int32, __int32);
	virtual void jumpOnce(void);
	virtual void postInfoTips(__int32);
	virtual void setAccumulatorState(float);
	virtual void sortPack(__int32);
	virtual void sortStorageBox(void);
	virtual __int32 enchant(__int32, __int32, __int32* const);  //370
	virtual __int32 enchantRandom(__int32);
	virtual __int32 canEnchant(__int32, __int32, __int32* const);
	virtual __int32 calcEnchantCost(__int32, __int32* const);
	virtual void setUserDataStr(__int32, std::string);
	virtual void writeLetters(__int32, std::string);
	virtual void writeBlueprint(__int32, std::string);
	virtual void writeInstruction(__int32, std::string);
	virtual __int32 repair(Vec3i);
	virtual bool canRepair(Vec3i);
	virtual __int32 calcRepairCost(Vec3i);  //380
	virtual __int32 NewRepair(Vec3i, Vec3i);
	virtual void changePlayerModel(__int32, __int32, char const*, char const*, __int32, __int32, bool);
	virtual void setCustomModelForActorBody(__int32, __int32, char const*, char const*, ActorBody*);
	virtual void getFullyCustomModelKey(void);
	virtual bool useSpecialItem(Vec3i);
	virtual void npcTrade(__int32, __int32, bool, __int32);
	virtual void starConvert(__int32);
	virtual void playBlockPlaceSound(Vec3i, __int32);
	virtual void playBlockDigSound(Vec3i, __int32);
	virtual char placeBlock(bool, Vec3i, unsigned __int32, DWORD, DWORD, __int32, __int32, __int32, DWORD, DWORD);     //1\xyz\1    //390
	virtual void summonAccountHorse(__int32);
	virtual void accountHorseEgg(void);
	virtual void avatarSummon(__int32);
	virtual void setSpectatorMode(unsigned __int32);
	virtual void setSpectatorType(unsigned __int32);
	virtual void getOPWay(void);
	virtual void setOPWay(__int32);
	virtual void changeOPWay(void);
	virtual void getCurWorldMapId(void);
	virtual void newAdNpcAddExp(__int32, __int32);//400
	virtual void tryBuyAdNpcGood(__int32, __int32);
	virtual void onBuyAdNpcGood(__int32, __int32);
	virtual void AddStar(__int32);
	virtual void completeTask(__int32);
	virtual void playAct(__int32);
	virtual void stopAct(void);
	virtual __int32 closeEditActorModel(__int32, std::string);
	virtual __int32 closeFullyCustomModelUI(__int32, std::string, std::string);
	virtual bool isShapeShift(void);
	virtual __int32 getSkinID(void);
	virtual __int32 summonPet(__int32, std::string, Vec3i, std::string);
	virtual void syncUseItemByHomeLand(__int32, __int32);
	virtual void setApiid(__int32);
	virtual __int32 getApiid(void);
	virtual void setLang(__int32);
	virtual __int32 getLang(void);
	virtual void setEnterTs(__int32);
	virtual __int32 getEnterTs(void);
	virtual __int32 UploadCheckInfo2Host(__int32, std::string const&);
	virtual void GetAdShopExtraItemReward(__int32, __int32, __int32);  //420
	virtual void ExtraStoreItem(__int32, __int32, __int32);
	virtual __int32 getSkinActPlayerNum(void);
	virtual __int32 getSkinActPlayerUinByIndex(__int32);
	virtual __int32 scanSkinActActorList(void);
	virtual bool playSkinAct(__int32, __int32, __int32);
	virtual void sendActorInvite(__int32, __int32, __int32);
	virtual void onAnimInterrupt(void);
	virtual bool checkCanPlaySkinAct(void);
	virtual bool checkHasEnoughSpace2SkinAct(__int32);
	virtual bool checkNearEnough2SkinAct(__int32);//430
	virtual bool checkIsDivByBlock(Vec2);
	virtual bool checkIsDivideByBlock(__int32);
	virtual World getSkinActTargetPos(__int32);
	virtual void addDirtyIndex(__int32);
	virtual void doPickActorByItemSkill(__int32, Vec3i, Vec3&, Vec3&);
	virtual void doPickBlockByItemSkill(__int32, Vec3&, Vec3&);
	virtual void doPickPhysicsActorByItemSkill(__int32, Vec3i, Vec3&, Vec3&);
	virtual void setHookObj(__int32, bool);
	virtual void setContainersPassword(World const&, __int32);
	virtual void setJumpState(__int32);  //440
	virtual void setStopState(bool);
	virtual void setCurrentMoveState(bool);
	virtual void updateRunState(void);
	virtual void getCarryingBindPos(void);
	virtual void SetTreeItemIndex(__int32, __int32);
	virtual void randomSelect(std::vector<PlayerAttrib const&>, __int32);
	virtual void onMoveTick(void);
	virtual bool openContainer(uintptr_t);
	virtual bool openContainer(World);
	virtual void closeContainer(void);
	virtual bool validServerBackPackLog(void);
	virtual void sub_000001(void);
	virtual void destroyBlock(Vec3i, __int32, bool, bool);
	virtual bool disMountEmitter(Vec3i const&);
	virtual bool disMountEmitterClient(Vec3i const&);
	virtual bool mountEmitter(Vec3i const&);
	virtual bool operateManualEmitter(Vec3i const&);
	virtual bool operateManualEmitterClient(Vec3i const&);
	virtual void fall(float);
	virtual float getFallHurtSubtract(void);
	virtual void canPlayStepSound(void);  //462
	virtual void canPlayHurtSound(void);
	virtual void getOpenContainerCom(void);
	virtual void getItemSkillComponent(void);
	virtual void changeMoveFlag(unsigned __int32, bool);
	virtual void onSetCurSprayPaint(bool);
	virtual void a_validServerBackPackLog(void);
	virtual void resetEyeDir(bool);
	virtual void tryMountActor(ActorBase*);
	virtual void shapeShift(void);
	virtual void tryWakeup(void);
	virtual void switchCurrentItem(void);
	virtual __int32 onInputEvent(std::string const&);
	virtual void tryShapeShift(__int32);
	virtual void trySleep(__int32);
	virtual void setViewMode(__int32, bool);
	virtual void setCurShortcut(__int32);
	virtual void setCurSprayPaint(bool);
	virtual __int32 doPick(bool, bool, bool);
	virtual void changeGameMode(__int32);
	virtual void doExchangeItems(__int32, __int32, __int32, __int32, __int32);  //482
	virtual __int32 lootItem(__int32, __int32);
	virtual void swapItem(__int32, __int32);
	virtual void mergeItem(__int32, __int32);
	virtual void discardItem(__int32, __int32);
	virtual void craftItem(__int32, __int32);
	virtual void setItem(Vec3i, char const&);
	virtual void setItemWithoutLimit(Vec3i, char const&, char const&);
	virtual void moveItem(Vec3i);
	virtual bool takeAccountItemsToHost(__int32, __int32);
	virtual void switchSkinActView(void);  //492
	virtual void tryCarryActor(ActorList*, Vec3i);
	virtual void setRefreshType(__int32);
	virtual void SendActionLog2Host(bool, std::string const&, std::string const&);
	virtual bool syncFullyCustomModelData(ActorPlayerList*);
	virtual void getScene(void);
	virtual void onMoveUp(__int32);
};
#pragma pack(pop)

class Player :public ActorBase {
};

class Attackedcomponent :public ActorBase {
};
class BackPackGrid :public Player {
};

class LocalPlayer :public Player {
private:
};


