#ifndef __BOMBERLOUTRE__
#define __BOMBERLOUTRE__

#include <Bomberloutre_map_item.ice>

module BomberLoutreInterface
{
	struct UserData
	{
		string gameTag;
		
		int gameCount;
		int winCount;
		int drawCount;
		
		int killCount;
		int deathCount;
		int suicideCount;
	};
	sequence<UserData> UserDataList;

	interface GameUserInterface
	{
		void userReady(UserData u);
	};

	struct GameData
	{
		string name;
		int roundCount;
		int state;
		int playerCount;
		GameUserInterface* gameui;
	};
	sequence<GameData> GameDataList;
	
	interface GameInterface
	{
		string getName();
		int getState();
		int getRoundCount();

		void setName(string newname);
		void setState(int newstate);
		void setRoundCount(int newcount);

		void kickPlayer(string username);
		void invitePlayer(string username);

		void addBot();
		void removeBot();

		bool createMap(string mode, string mapSkin);
		
		void startMap();
		void endMap();
		
		bool removeGame();
	};
	
	interface GameWaitRoom
	{
		void newUserInRoom(string username);
		void userLeftRoom(string username);
		
		void allUsersReady();
		void userReady(string username);
		
		void gameDataUpdated(GameData g);
		
		void gameStart();
		void gameEnd();
	};
	
	struct Player
	{
		int posX;
		int posY;
		
		int width;
		int height;
		
		int killCount;
		int deathCount;
		int suicideCount;
		
		UserData related;
	};
	sequence<Player> PlayerList;
	
	struct Point
	{
		int x;
		int y;
	};

	interface MapInterface
	{
		string getId();
		int getWidth();
		int getHeight();
		
		void moveUp(Player p);
		void moveDown(Player p);
		void moveLeft(Player p);
		void moveRight(Player p);
		
		void dropBomb(Player p, Bomb b);
	};

	struct Map
	{	
		MapInterface* mi;
		MapItems items;
		PlayerList players;
	};

	interface MapObserver
	{
		void refreshMapItems(MapItems mi);
		void refreshPlayers(PlayerList p);
		
		void bombHasBeenPlanted(Bomb b);
		void bombExploded(Bomb b);
		void bombKicked(Bomb b, Point dest);
		
		void bonusesDropped(Bonuses b);
		
		void playerDied(Player p);
	};

	exception UserException { string reason; };
	exception BadLoginException 				extends UserException {};
	exception BadPasswordException 			extends UserException {};
	exception UserAlreadyExistsException 	extends UserException {};

	interface ServerInterface
	{	
		UserData connect(string login, string password)
			throws BadLoginException, BadPasswordException;
		UserData createUser(string login, string password)
			throws UserAlreadyExistsException;
		bool deleteUser(string login);
		
		GameInterface* addGame(string name, UserData user, GameWaitRoom* room, MapObserver* mo);
		Map				joinGame(string name, UserData user, GameWaitRoom* room, MapObserver* mo);
		GameDataList	getGameList();
		UserDataList	getUserList();
	};
};

#endif
