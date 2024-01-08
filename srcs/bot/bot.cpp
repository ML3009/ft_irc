/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: purple <purple@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 16:00:35 by purple            #+#    #+#             */
/*   Updated: 2024/01/08 10:31:57 by purple           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "irc.hpp"




/*----------------- Coplien ------------- */

bot::bot(){
    
    _factmap[0] = "IRC a été inventé par Jarkko Oikarinen en 1988. À l'origine, il s'agissait d'un moyen pour les étudiants de l'Université d'Oulu en Finlande de communiquer.";
    _factmap[1] = "Le terme 'canal' dans IRC fait référence à un canal de discussion, où plusieurs utilisateurs peuvent discuter en temps réel. Les canaux sont précédés du symbole '#' (par exemple, #chat).";
    _factmap[2] = "Les utilisateurs qui ont des droits spéciaux sur un canal sont appelés opérateurs de canal. Ils peuvent modérer la discussion et gérer les utilisateurs.";
    _factmap[3] = "Les commandes IRC commencent généralement par un '/' (par exemple, /join pour rejoindre un canal, /nick pour changer de pseudonyme).";
    _factmap[4] = "IRC fonctionne sur un réseau de serveurs interconnectés. Chaque serveur peut héberger plusieurs canaux de discussion.";
    _factmap[5] = "IRC est basé sur un protocole ouvert, ce qui signifie que n'importe qui peut mettre en place son propre serveur IRC ou implémenter un client IRC.";
    _factmap[6] = "Les canaux IRC peuvent avoir différents modes, tels que le mode secret (où le canal n'apparaît pas dans la liste des canaux) ou le mode modéré (limitant qui peut envoyer des messages).";
    _factmap[7] = "Les bots IRC sont des programmes automatisés qui peuvent effectuer diverses tâches sur les canaux, comme la modération, la diffusion d'informations ou la gestion de jeux.";
    _factmap[8] = "Il existe de nombreux clients IRC disponibles, des clients en ligne de commande classiques tels que Irssi aux clients graphiques modernes tels que HexChat.";
    _factmap[9] = " IRC a survécu à l'épreuve du temps malgré l'émergence de nouvelles technologies de messagerie. Il reste populaire pour les communautés de discussion en ligne.";
    _name = "ROOOOHBot";
}

bot::bot(const bot& rhs){
    *this = rhs;
}

bot &bot::operator=(const bot& rhs){
    if (this != &rhs)
        *this = rhs;
    return *this;
}

bot::~bot(){

}

/*---------- Getter / Setter ------------ */

std::string bot::getName() const {return _name;}
/*--------------- Function -------------- */

void bot::sayhello(server &server, user &client){
    server.sendMsgFromBot(*this, client ,server, "Hi ! you call me without anything :(\n You can ask me for help with"
                                                    + std::string(BLU) +" @bot HELP" + COLOR_RESET 
                                                    +"\n\tor\nask for a fact with "+ std::string(BLU) +"@bot FACT"+ COLOR_RESET);    
}

void bot::help(server &server, user &client){
    std::string msg = CYN + std::string("\n\t[HELP]\n") + COLOR_RESET
                    + YEL + "[COMMANDS]\n" + COLOR_RESET
                    + MAG + "PASS [password] " + COLOR_RESET + ": Entrer the serveur password\n"
                    + MAG + "NICK [nickname] " + COLOR_RESET + ": Set up your nickname\n"
                    + MAG + "USER [username] [x] [x] [realname] " + COLOR_RESET + ": Set up your user informations\n"
                    + MAG + "PRIVMSG [user] [message] " + COLOR_RESET + ": Send a private message to someone\n"
                    + MAG + "PRIVMSG [#channe] [message] " + COLOR_RESET + ": Send a message to a channel\n"
                    + MAG + "JOIN [#channel] " + COLOR_RESET + ": Join or create a channel\n"
                    + MAG + "KICK [#channel] [name] " + COLOR_RESET + ": Kick someone from the channel\n"
                    + MAG + "MODE [#channel] [options] " + COLOR_RESET + ": Set or Unset a channel option\n"
                    + MAG + "INVITE [user] [#channel] " + COLOR_RESET + ": Invite an user on the channel\n"
                    + MAG + "TOPIC [#channel] [topic] " + COLOR_RESET + ": Set a topic for the channel\n"
                    + MAG + "PART [#channel] [reason]* " + COLOR_RESET + ": Leave a channel. the reason is optionnal\n"
                    + MAG + "QUIT [reason] " + COLOR_RESET + ": Disconnect from the server. reason is optionnal\n"
                    + YEL + "\n[MODE]\n" + COLOR_RESET
                    + CYN + "use /MODE [argument] to set a mode\n" + COLOR_RESET
                    + MAG + "[i] " + COLOR_RESET + ": Set the channel to Invite only\n"
                    + MAG + "[t] " + COLOR_RESET + ": Set a admin restriction to the TOPIC command\n"
                    + MAG + "[k] " + COLOR_RESET + ": Set a channel password\n"
                    + MAG + "[o] " + COLOR_RESET + ": Set an user to operator\n"
                    + MAG + "[l] " + COLOR_RESET + ": Set a user limit to a channel\n"
                    + YEL + "\n[BOT]\n" + COLOR_RESET
                    + CYN + "use @bot [argument] to use the bot\n" + COLOR_RESET
                    + MAG + "HELP " + COLOR_RESET + ": Show all the commands\n"
                    + MAG + "FACT " + COLOR_RESET + ": Show a random fact about irc server\n"
                    + MAG + " " + COLOR_RESET + ": Bot will say hello\n";
    server.sendMsgFromBot(*this, client ,server, msg);
}

void bot::getfact(server &server, user &client, int fact){
    server.sendMsgFromBot(*this, client ,server, _factmap[fact]);
}
/*--------------- Exception ------------- */
