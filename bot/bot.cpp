/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <medpurple@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:00:35 by purple            #+#    #+#             */
/*   Updated: 2024/01/21 22:04:58 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bot.hpp"


bool handleSignalbot	= false;
bool quizz_on           = false;
int  quizzUser          = 0;
int  serverfd           = 0;
std::vector<std::string> quizzAnswer;
std::string quizzdest;
int  question = 0;
int main(int ac, char **av){
    if (ac != 2)
        return 1;
    const char* serverIP = "127.0.0.1";
    const int serverPort = 6667;
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Erreur lors de la création du socket" << std::endl;
        return 1;
    }
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIP, &serverAddress.sin_addr);
    if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1) {
        std::cerr << "Erreur lors de la connexion au serveur" << std::endl;
        close(clientSocket);
        return 1;
    }
    std::string joinMessage = "@initialisation " + std::string(av[1]) + "\r\n";
    send(clientSocket, joinMessage.c_str(), joinMessage.size(), 0);
    char buffer[1024];
    while (!(handleSignalbot)){
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead == -1)
            std::cerr << "Erreur lors de la réception des données du serveur" << std::endl;
        else {
            buffer[bytesRead] = '\0';
            std::vector<std::string> argument = splitArgs(buffer);
            std::cout << "RECEPTION" << std::endl;
            for (size_t i = 0; i < argument.size(); i++)
                std::cout << "[" + std::string(argument[i]) + "]" << std::endl;
            std::cout << "----------------" << std::endl;
            execute(argument);
            memset(buffer, 0, 512);
        }
    }
    close(clientSocket);
    return 0;
}

std::vector<std::string> splitArgs(std::string buffer){
    std::vector<std::string> args;
    char *arg = strtok((char *)buffer.c_str(), "\r\n ");
    while (arg != NULL && !buffer.empty())
    {
        args.push_back(arg);
        arg = strtok(NULL, "\r\n ");
    }
    return args;
}

int botcmd(std::string arg){
    std::string cmd[5] = {"HELP", "FACT", "HI", "QUIZZ", "DFT"};
    for (int i = 0; i < 5; i++){
        if (cmd[i] == arg)
            return i;
    }
    return -1;
}

void execute(std::vector<std::string> argument){
    std::cout << "QUIZZ MOD " << quizz_on << std::endl;
    if (quizz_on && argument.size() > 0)
    {
        std::ostringstream oss;
        oss << quizzUser;
        std::cout << "1" << std::endl;
        std::cout << "USER : " << oss.str() << std::endl;
        quizzAnswer.push_back(argument[0]);
        quizzUser--;
        if (quizzUser == 0){
            std::cout << "2" << std::endl;
            quizz_on = false;
            if (send(serverfd, reponsetoQuizz().c_str(),  reponsetoQuizz().length(), 0) == -1)
                std::perror("send:");
            question = 0;
        }
        return;
    }
    if (argument.size() != 3 && (argument.size() != 4 && argument[1] == "QUIZZ"))
        return;
    switch (botcmd(argument[1]))
	{
		case HELP:
            if (send(atoi(argument[2].c_str()), helpBot(argument[0]).c_str(),  helpBot(argument[0]).length(), 0) == -1)
                std::perror("send:");
			break;
		
        case FACT:
			if (send(atoi(argument[2].c_str()), sendFact(argument[0]).c_str(), sendFact(argument[0]).length(), 0) == -1){
			 	std::perror("send:");}
			break;
		
        case HI:
		    if (send(atoi(argument[2].c_str()), sayhello(argument[0]).c_str(), sayhello(argument[0]).length(), 0) == -1){
		 	     std::perror("send:");}
			break;
		
        case QUIZZ:
            quizzUser = atoi(argument[3].c_str());
            quizzdest = argument[0];
            quizz_on = true;
            serverfd = atoi(argument[2].c_str());
			if (send(atoi(argument[2].c_str()), startquizz(argument[0]).c_str(), startquizz(argument[0]).length(), 0) == -1){
		     	std::perror("send:");}
			break;
        
        default:
	    	if (send(atoi(argument[2].c_str()), saynothing(argument[0]).c_str(), saynothing(argument[0]).length(), 0) == -1){
		    	std::perror("send:");}    
			break;;
	}
}


// /*--------------- Function -------------- */
std::string startquizz(std::string dest){
    std::srand(std::time(0));
    question = std::rand() % 5;
    std::string _quizzmap[5]; 
    _quizzmap[0] = "Capitale du Japon ?";
    _quizzmap[1] = "Nombre de continents sur Terre ?";
    _quizzmap[2] = "Langue parlée en Espagne ?";
    _quizzmap[3] = "Métal liquide à température ambiante ?";
    _quizzmap[4] = "Nombre de côtés dans un hexagone ?";

    return  std::string("### ") + dest + "\r\n"
            + _quizzmap[question] + "\r\n"
            + "###\r\n";
}

std::string sendFact(std::string dest){
    std::srand(std::time(0));
    std::string _factmap[10]; 
    _factmap[0] =  "IRC was invented by Jarkko Oikarinen in 1988. Originally, it was a means for students at the University of Oulu in Finland to communicate.\r\n";
    _factmap[1] =  "The term 'channel' in IRC refers to a discussion channel where multiple users can chat in real-time. Channels are prefixed with the '#' symbol (e.g., #chat).\r\n";
    _factmap[2] =  "Users with special privileges on a channel are called channel operators. They can moderate discussions and manage users.\r\n";
    _factmap[3] =  "IRC commands typically start with a '/' (e.g., /join to join a channel, /nick to change a nickname).\r\n";
    _factmap[4] =  "IRC operates on a network of interconnected servers. Each server can host multiple discussion channels.\r\n";
    _factmap[5] =  "IRC is based on an open protocol, meaning anyone can set up their own IRC server or implement an IRC client.\r\n";
    _factmap[6] =  "IRC channels can have different modes, such as secret mode (where the channel doesn't appear in the channel list) or moderated mode (limiting who can send messages).\r\n";
    _factmap[7] =  "IRC bots are automated programs that can perform various tasks on channels, such as moderation, information broadcasting, or game management.\r\n";
    _factmap[8] =  "There are numerous IRC clients available, from classic command-line clients like Irssi to modern graphical clients like HexChat.\r\n";
    _factmap[9] =  "IRC has stood the test of time despite the emergence of new messaging technologies. It remains popular for online discussion communities.\r\n";

    return  std::string("@@@ ") + dest + "\r\n"
            + _factmap[std::rand() % 10] + "\r\n"
            + "@@@\r\n";
}
std::string saynothing(std::string dest){
    return  std::string("@@@ ") + dest + "\r\n" 
            + "Hi ! you call me without anything :(\r\n" +
            + "You can ask me for help with"
            + std::string(BLU) +" @bot HELP" + COLOR_RESET + "\r\n"
            + "@@@\r\n";
}

std::string sayhello(std::string dest){
    return  std::string("@@@ ") + dest + "\r\n" 
            + "Hi ! How are you today ?\r\n"
            + "@@@\r\n";
}


std::string helpBot(std::string dest){
    return  std::string("@@@ ") + dest + "\r\n"
            + CYN + "\t[HELP]" + COLOR_RESET + "\r\n"
            + YEL + "[COMMANDS]" + COLOR_RESET + "\r\n"
            + MAG + "PASS [password] " + COLOR_RESET + ": Entrer the serveur password" + "\r\n"
            + MAG + "NICK [nickname] " + COLOR_RESET + ": Set up your nickname" + "\r\n"
            + MAG + "USER [username] [x] [x] [realname] " + COLOR_RESET + ": Set up your user informations" + "\r\n"
            + MAG + "PRIVMSG [user] [message] " + COLOR_RESET + ": Send a private message to someone" + "\r\n"
            + MAG + "PRIVMSG [#channe] [message] " + COLOR_RESET + ": Send a message to a channel" + "\r\n"
            + MAG + "JOIN [#channel] " + COLOR_RESET + ": Join or create a channel" + "\r\n"
            + MAG + "KICK [#channel] [name] " + COLOR_RESET + ": Kick someone from the channel" + "\r\n"
            + MAG + "MODE [#channel] [options] " + COLOR_RESET + ": Set or Unset a channel option" + "\r\n"
            + MAG + "INVITE [user] [#channel] " + COLOR_RESET + ": Invite an user on the channel" + "\r\n"
            + MAG + "TOPIC [#channel] [topic] " + COLOR_RESET + ": Set a topic for the channel" + "\r\n"
            + MAG + "PART [#channel] [reason]* " + COLOR_RESET + ": Leave a channel. the reason is optionnal" + "\r\n"
            + MAG + "QUIT [reason] " + COLOR_RESET + ": Disconnect from the server. reason is optionnal" + "\r\n"
            + MAG + "NAMES [#channel] " + COLOR_RESET + ": Display all user in a channel. channel is optionnal" + "\r\n"
            + YEL + "[MODE]" + COLOR_RESET + "\r\n"
            + CYN + "use /MODE [argument] to set a mode" + COLOR_RESET + "\r\n"
            + MAG + "[i] " + COLOR_RESET + ": Set the channel to Invite only" + "\r\n"
            + MAG + "[t] " + COLOR_RESET + ": Set a admin restriction to the TOPIC command" + "\r\n"
            + MAG + "[k] " + COLOR_RESET + ": Set a channel password" + "\r\n"
            + MAG + "[o] " + COLOR_RESET + ": Set an user to operator" + "\r\n"
            + MAG + "[l] " + COLOR_RESET + ": Set a user limit to a channel" + "\r\n"
            + YEL + "[BOT]" + COLOR_RESET + "\r\n"
            + CYN + "use @bot [argument] to use the bot" + COLOR_RESET + "\r\n"
            + MAG + "HELP " + COLOR_RESET + ": Show all the commands\n" + "\r\n"
            + MAG + "FACT " + COLOR_RESET + ": Show a random fact about irc server" + "\r\n"
            + MAG + "RPS " + COLOR_RESET + ": Show a random fact about irc server" + "\r\n"
            + MAG + "HI " + COLOR_RESET + ": Show a random fact about irc server" + "\r\n" 
            + "@@@\r\n";
}

std::string reponsetoQuizz(){
    int correct = 0;
    std::ostringstream ossok;
    std::string _answermap[5]; 
    _answermap[0] = "tokyo";
    _answermap[1] = "7";
    _answermap[2] = "espagnol";
    _answermap[3] = "mercure";
    _answermap[4] = "6";

    for (int i = 0; i < quizzAnswer.size(); i++)
        if (quizzAnswer[i] == _answermap[question])
            correct++;
    ossok << correct;
    return  std::string("!!! ") + quizzdest + "\r\n"
            + "The correct answer was : " + _answermap[question] + "\r\n"
            + ossok.str() + " people find the good answer ! good job everyone ;)" + "\r\n"
            + "!!!\r\n";
    
}
/*--------------- Exception ------------- */
