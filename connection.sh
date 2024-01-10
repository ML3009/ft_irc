#!/bin/bash

# Remplacez les valeurs suivantes par vos propres informations
server="localhost"
port="6667"
channel="le canal que vous souhaitez rejoindre"
password="test"

# Vérifie si le pseudo est passé en argument
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <pseudo>"
    exit 1
fi

nick="$1"

# Connexion au serveur IRC
{
  echo -e "/PASS $password"
  sleep 1
  echo -e "/NICK $nick"
  sleep 1
  echo -e "/USER $nick $nick $nick $nick"
  sleep 1
  # Lire les commandes depuis l'entrée standard
  while IFS= read -r command; do
    echo -e "$command"
    sleep 1
  done
} | nc -C $server $port
