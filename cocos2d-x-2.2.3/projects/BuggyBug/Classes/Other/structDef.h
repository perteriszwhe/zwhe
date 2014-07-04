#ifndef __COMMON_H__
#define __COMMON_H__

#include <string>
#include <map>
#include <vector>

//成就
typedef struct AchieveStructTag
{
	int id;
	const char *key;
	const char *value;
	bool progress;
	bool show;
} AchieveStruct;

typedef std::map<int,AchieveStruct> MapAchieve;
typedef MapAchieve::iterator MapAchieveIt;

//动画
struct AnimationStruct
{
	std::string		id;
	int				startIdx;
	int				endIdx;
	std::string		nameRule; 
	float			frequency;
};

typedef	std::map<std::string,AnimationStruct> MapAnimation;
typedef MapAnimation::iterator MapAnimationIt;

//人物
struct CharacterStruct 
{
	int id;
	std::string standing;
	std::string sitting;
	std::string running;
	std::string walking;
	std::string sleeping;
	std::string squatting;
	std::string name;
	std::string initHero;
	std::string shadowImg;
	std::string dodging;
};
typedef std::map<int,CharacterStruct> MapCharacter;
typedef MapCharacter::iterator MapCharacterIt;

//事件
struct EventStruct
{
	int id;
	int type;
	std::string animationKey;
	int target;
};

typedef std::map<int,EventStruct> MapEvent;
typedef MapEvent::iterator MapEventIt;

//图片
struct ImageStruct 
{
	std::string id;
	std::string path;
};

typedef std::map<std::string,ImageStruct> MapImage;
typedef MapImage::iterator MapImageIt;

//地图
struct LoadMapStruct
{
	std::string id;
	std::string bgImg01;
	std::string bgImg02;
	std::string bgImg03;
	std::string tmxFile;
};

typedef std::map<std::string,LoadMapStruct> MapLoader;
typedef MapLoader::iterator MapLoaderIt;

//说话
struct SpeakStruct
{
	int id;
	int type;
	int roleId;
	int eventId;
	std::string role;
	std::string content;
	std::string animationKey;
	int nextId;
} ;

typedef std::map<int,SpeakStruct> MapSpeak;
typedef MapSpeak::iterator MapSpeakIt;

//字符串
struct R
{
	std::string id;
	std::string name;
	std::string desc;
};

typedef std::map<std::string,R> MapStr;
typedef std::map<std::string,R>::iterator MapStrIt;

//任务
struct TaskStruct
{
	int id;
	std::string desc;
	int nextId;
};

typedef std::map<int,TaskStruct> MapTask;
typedef MapTask::iterator MapTaskIt;

//属性
struct PropertyStruct
{
	int			id;
	std::string key;
	std::string name;
	std::string value;
};

struct AntPropertyStruct
{
	int			id;
	std::string key;
	std::string name;
	std::string value;
};

struct LevelPropertyStruct
{
	int			id;
	std::string type;
	std::string ant;
    std::string describe;
	std::string number;
};

struct ItemPropertyStruct
{
	int			id;
	std::string imageFile;
    std::string playImage;
    int cdTime;
	std::string price;
    int number;
    int type;
    std::string describe;
};
//角色
struct RoleStruct 
{
	int			id;
	std::string name;
	std::map<int,PropertyStruct> attributes;
	std::vector<std::string> descs;
};

typedef std::map<int,RoleStruct> MapRole;
typedef MapRole::iterator  MapRoleIt;
typedef std::map<int,PropertyStruct> MapProperty;
typedef MapProperty::iterator MapPropertyIt;

struct AntStruct
{
	int			id;
	std::string name;
    std::string spineFile;
	std::map<int,AntPropertyStruct> attributes;
	std::vector<std::string> descs;
};

typedef std::map<int,AntStruct> MapAnt;
typedef MapAnt::iterator  MapAntIt;
typedef std::map<int,AntPropertyStruct> AntProperty;
typedef AntProperty::iterator AntPropertyIt;

struct LevelStruct
{
	int			id;
	std::string name;
    std::string time;
	std::map<int,LevelPropertyStruct> attributes;
};

typedef std::map<int,LevelStruct> MapLevel;
typedef MapLevel::iterator  MapLevelIt;
typedef std::map<int,LevelPropertyStruct> LevelProperty;
typedef LevelProperty::iterator LevelPropertyIt;

struct ItemStruct
{
	int			id;
	std::string name;
	std::map<int,ItemPropertyStruct> attributes;
};

typedef std::map<int,ItemStruct> MapItem;
typedef MapItem::iterator  MapItemIt;
typedef std::map<int,ItemPropertyStruct> ItemProperty;
typedef ItemProperty::iterator ItemPropertyIt;

struct AntInfo
{
	int	totalBlood;
    int	currentBlood;
    int	damage;
    float goInSpeed;
    float comeBackSpeed;
};

enum Hero
{
	hero_manxia = 1,//盲侠
	hero_jiandaoshou, // 剪刀手
	hero_baili,//百里大侠
};

enum Hero_Posture
{
	posture_standing = 1,//站姿
	posture_sitting,//坐姿
	posture_running,//跑姿
	posture_walking,//走姿
	posture_sleeping,//睡姿
	posture_squatting,//蹲姿
	posture_dodoging,//闪躲
};

enum Direction
{
	dir_left = 1,
	dir_right,
	dir_top,
	dir_bottom,
	dir_stop,
};

#endif