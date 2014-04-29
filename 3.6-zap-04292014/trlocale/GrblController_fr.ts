<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="fr_FR">
<context>
    <name>About</name>
    <message>
        <location filename="../about.ui" line="14"/>
        <source>About...</source>
        <translation>A propos ...</translation>
    </message>
    <message>
        <location filename="../about.ui" line="61"/>
        <source>The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.</source>
        <translation>Le programme est fourni en l&apos;état SANS GARANTIE D&apos;AUCUNE SORTE, MEME LES GARANTIES DE CONCEPTION, MARCHANDE ET D&apos;ADAPTATION À UN USAGE PARTICULIER.</translation>
    </message>
    <message>
        <location filename="../about.ui" line="84"/>
        <source>Grbl Controller</source>
        <translation>Controleur Grbl</translation>
    </message>
    <message>
        <source>Grbl Controller 4</source>
        <translation type="obsolete">Controleur Grbl 4</translation>
    </message>
</context>
<context>
    <name>GCode</name>
    <message>
        <location filename="../gcode.cpp" line="45"/>
        <source>Can&apos;t open COM port </source>
        <translation>Impossible d&apos;ouvrir le port série  </translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="50"/>
        <source>-Is hardware connected to USB?</source>
        <translation>- le périphérique est-il bien connecté sur un port USB ?</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="51"/>
        <source>-Is correct port chosen?</source>
        <translation>- le port choisi est-il correct ?</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="52"/>
        <source>-Does current user have sufficient permissions?</source>
        <translation>- l&apos;utilisateur a-t-il les droits d&apos;utilisation suffisants ?</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="172"/>
        <source>SENDING: 0x%02X (CTRL-X) to check presence of Grbl
</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="175"/>
        <location filename="../gcode.cpp" line="431"/>
        <source>Sending to port failed</source>
        <translation>L&apos;émission vers le port a échoué</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="331"/>
        <source>Got Grbl Version (Parsed:) %d.%d%c ($$=%d)
</source>
        <translation>Vous avez la version Grbl (analysée)  %d.%d%c ($$=%d)\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="348"/>
        <source>Port not available yet</source>
        <translation>Le port n&apos;est plus disponible</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="396"/>
        <source>Buffer size too small</source>
        <translation>Le tampon est trop petit</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="406"/>
        <source>SENDING[%d]: 0x%02X (CTRL-X)
</source>
        <translation>EMISSION[%d]: 0x%02X (CTRL-X)\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="408"/>
        <source>SENDING[%d]: %s
</source>
        <translation>EMISSION[%d]: %s\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="442"/>
        <source>WAITFOROK FAILED
</source>
        <translation>Echec lors de l&apos;attente de Ok </translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="448"/>
        <source>Wait for ok failed</source>
        <translation>L&apos;attente d&apos;un bon déroulement a échouée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="542"/>
        <location filename="../gcode.cpp" line="756"/>
        <source>Error reading data from COM port
</source>
        <translation>Erreur de lecture des données dur le port série</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="564"/>
        <source>Unexpected: list is empty (o)!</source>
        <translation>Liste inattendue vide (o) </translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="569"/>
        <location filename="../gcode.cpp" line="587"/>
        <source>GOT[%d]:%s for %s
</source>
        <translation>Vous avez [%d]:%s pour %s\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="580"/>
        <source>Error?</source>
        <translation>Erreur non répertoriée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="582"/>
        <source>Unexpected: list is empty (e)!</source>
        <translation>Liste inattendue vide (e) </translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="602"/>
        <location filename="../gcode.cpp" line="640"/>
        <location filename="../gcode.cpp" line="767"/>
        <source>GOT:%s
</source>
        <translation>Vous avez : %s\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="707"/>
        <source>Wait interrupted by user</source>
        <translation>Attente d&apos;interuption par l&apos;utilisateur</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="775"/>
        <source>Expecting Grbl version string. Unable to parse response.</source>
        <translation>Attente de la version Grbl, impossible d&apos;analyser la réponse</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="799"/>
        <source>No data from COM port after connect. Expecting Grbl version string.</source>
        <translation>Aucune données depuis le port série après la connexion, en attente de la version Grbl</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="820"/>
        <source>Wait interrupted by user (startup)</source>
        <translation>Attente d&apos;interuption par l&apos;utilisateur (démarrage)</translation>
    </message>
    <message>
        <source>XYUV-Rate Limit FIX: [%1]=&gt;[%2]</source>
        <translation type="obsolete">Correction de la limite de vitesse XYUV : [%1]=&gt;[%2]</translation>
    </message>
    <message>
        <source>([a-zA-Z]+),MPos:</source>
        <translation type="obsolete">([a-zA-Z]+),PosM :</translation>
    </message>
    <message>
        <source>([a-zA-Z]+), MPos:</source>
        <translation type="obsolete">([a-zA-Z]+) ,PosM :</translation>
    </message>
    <message>
        <source>MPos:</source>
        <translation type="obsolete">PosM :</translation>
    </message>
    <message>
        <source>WPos:</source>
        <translation type="obsolete">PosT :</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="945"/>
        <source>Decoded: State:%s MPos: %f,%f,%f WPos: %f,%f,%f
</source>
        <translation>Décodage : Etat :%s MPos: %f,%f,%f WPos: %f,%f,%f
</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="951"/>
        <source>Decoded: State:%s MPos: %f,%f,%f,%f WPos: %f,%f,%f,%f
</source>
        <translation>Décodage : Etat :%s MPos: %f,%f,%f,%f WPos: %f,%f,%f,%f
</translation>
    </message>
    <message>
        <source>Error decoding position data!
</source>
        <translation type="obsolete">Erreur de décodage des données de position\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="905"/>
        <source>Incorrect - extra axis present in hardware but options set for only 3 axes. Please fix options.</source>
        <translation>L&apos;axe supplémentaire existe matériellement. Veuillez corriger les options en cochant 4 ème axe.</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="914"/>
        <source>Incorrect - extra axis not present in hardware but options set for &gt; 3 axes. Please fix options.</source>
        <translation>L&apos;axe supplémentaire n&apos;existe pas matériellement. Veuillez corriger les options  en décochant 4 ème axe.</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1003"/>
        <source>GOT-TE:%s
</source>
        <translation>Vous avez -TE :%s\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1026"/>
        <source>Sending file &apos;%1&apos;</source>
        <translation>Emission du fichier &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1173"/>
        <source>Gave up waiting for OK
</source>
        <translation>Fin d&apos;attent Ok\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1192"/>
        <source>Code sent successfully with %1 error(s):</source>
        <translation>Code émis correctement avec %1 erreur(s)</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1204"/>
        <source>Code sent successfully with no errors.</source>
        <translation>Code émis correctement sans erreur</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1211"/>
        <source>Filtered %1 commands:</source>
        <translation>Commande filtrée %1</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1224"/>
        <source>Process interrupted.</source>
        <translation>Processus interrompu</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1258"/>
        <source>Removed unsupported command &apos;%1&apos; part of &apos;%2&apos;</source>
        <translation>Suppression de la commande &apos;%1&apos; portion de &apos;%2 ( non supportée)</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1274"/>
        <source>Removed unsupported G command &apos;%1&apos;</source>
        <translation>Suppression de la commande G  &apos;%1&apos;  non supprortée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1287"/>
        <source>Removed unsupported M command &apos;%1&apos;</source>
        <translation>Suppression de la commande M  &apos;%1&apos;  non supprortée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1306"/>
        <source>Removed unsupported command &apos;%1&apos;</source>
        <translation>Suppression de la commande &apos;%1&apos;  non supprortée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1439"/>
        <source>Unable to remove enough decimal places for command (will be truncated): %s</source>
        <translation>Impossible de supprimer assez de décimales pour la commande (sera tronqué) %s</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1443"/>
        <source>Error, insufficent reduction &apos;%1&apos;</source>
        <translation>Erreur : réduction insuffisante  &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1445"/>
        <source>Precision reduced &apos;%1&apos;</source>
        <translation>Précision réduite  &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1641"/>
        <source>Z-Rate Limit: [%1]=&gt;[%2]</source>
        <translation>Limite de vitesse Z  [%1]=&gt;[%2]</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1646"/>
        <source>Z-Rate Limit: [%1]=&gt;[%2,%3]</source>
        <translation>Limite de vitesse Z :  [%1]=&gt;[%2,%3]</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1691"/>
        <source>XY-Rate Limit FIX: [%1]=&gt;[%2]</source>
        <translation>Correction de la limite de vitesse XY : [%1]=&gt;[%2]</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1750"/>
        <source>Bad command: %1</source>
        <translation>Commande erronée : %1</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1854"/>
        <source>Options specify use mm but Grbl parser set for inches. Fixing.</source>
        <translation>Vous utiliser les mm alors que l&apos;analyse indique des pouces. Corriger</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1859"/>
        <source>Options specify use inches but Grbl parser set for mm. Fixing.</source>
        <translation>Vous devez utiliser les pouces alors que l&apos;analyse indique des mm. Corriger</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1873"/>
        <source>Options specify use mm but Grbl reporting set for inches. Fixing.</source>
        <translation>Vous utiliser les mm alors que Grbl donne despouces. Corriger</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1878"/>
        <source>Options specify use inches but Grbl reporting set for mm. Fixing.</source>
        <translation>Vous utiliser les pouces alors que Grbl donne des mm. Corriger</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1914"/>
        <location filename="../gcode.cpp" line="1915"/>
        <source>(mm)</source>
        <translation>(mm)</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1919"/>
        <location filename="../gcode.cpp" line="1920"/>
        <source>(in)</source>
        <translation>(pouce)</translation>
    </message>
</context>
<context>
    <name>GrblDialog</name>
    <message>
        <location filename="../grbldialog.ui" line="20"/>
        <source>Grbl Settings</source>
        <translation>Configuration GRBL</translation>
    </message>
    <message>
        <location filename="../grbldialog.ui" line="32"/>
        <source>Apply</source>
        <translation>Appliquer</translation>
    </message>
    <message>
        <location filename="../grbldialog.ui" line="45"/>
        <source>Close</source>
        <translation>Fermer</translation>
    </message>
    <message>
        <location filename="../grbldialog.cpp" line="29"/>
        <source>Value</source>
        <translation>Valeur</translation>
    </message>
    <message>
        <location filename="../grbldialog.cpp" line="29"/>
        <source>Item</source>
        <translation>Elément</translation>
    </message>
</context>
<context>
    <name>Log4Qt::AppenderSkeleton</name>
    <message>
        <location filename="../log4qt/appenderskeleton.cpp" line="137"/>
        <source>Activation of appender &apos;%1&apos; that requires layout and has no layout set</source>
        <translation>Activation de  &apos;Appender&apos;  &apos;%1&apos;  lequel nécessite une mise en page  non réalisée ! </translation>
    </message>
    <message>
        <location filename="../log4qt/appenderskeleton.cpp" line="228"/>
        <source>Use of non activated appender &apos;%1&apos;</source>
        <translation>Utilisation de  &apos;Appender&apos;  &apos;%1&apos; non activé</translation>
    </message>
    <message>
        <location filename="../log4qt/appenderskeleton.cpp" line="236"/>
        <source>Use of closed appender &apos;%1&apos;</source>
        <translation>Utilisation de  &apos;Appender&apos;  &apos;%1&apos; fermé</translation>
    </message>
    <message>
        <location filename="../log4qt/appenderskeleton.cpp" line="244"/>
        <source>Use of appender &apos;%1&apos; that requires layout and has no layout set</source>
        <translation>Utiliser &apos;Appender&apos;  &apos;%1&apos;  lequel nécessite une mise en page  non réalisée ! </translation>
    </message>
</context>
<context>
    <name>Log4Qt::DailyRollingFileAppender</name>
    <message>
        <location filename="../log4qt/dailyrollingfileappender.cpp" line="148"/>
        <source>Use of appender &apos;%1&apos; without having a valid date pattern set</source>
        <translation>Utiliation de  &apos;Appender&apos;  &apos;%1&apos; sans un modèle valide initialisé</translation>
    </message>
    <message>
        <location filename="../log4qt/dailyrollingfileappender.cpp" line="215"/>
        <source>The pattern &apos;%1&apos; does not specify a frequency for appender &apos;%2&apos;</source>
        <translation>Le modème &apos;%1&apos;  ne spécifie aucune fréquence pour 4Appender&apos; &apos;%2&apos;</translation>
    </message>
</context>
<context>
    <name>Log4Qt::Factory</name>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="262"/>
        <source>Cannot convert to type &apos;%1&apos; for property &apos;%2&apos; on object of class &apos;%3&apos;</source>
        <translation>La conversion de type &apos;%1&apos; de la propriété &apos;%2&apos; de l&apos;objet de classe &apos;%3&apos; est impossible.</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="375"/>
        <source>Unable to set property value on object</source>
        <translation>Impossible d&apos;inialiser la valeur de la propriété de l&apos;objet.</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="381"/>
        <source>Invalid null object pointer</source>
        <translation>Pointeur d&apos;objet &apos;null&apos; invalide</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="390"/>
        <source>Invalid empty property name</source>
        <translation>Nom de propriété invalide (vide)</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="408"/>
        <source>Property &apos;%1&apos; does not exist in class &apos;%2&apos;</source>
        <translation>La propriété &apos;%1&apos; n&apos;existe pas dans la classe &apos;%2&apos;</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="421"/>
        <source>Property &apos;%1&apos; is not writable in class &apos;%2&apos;</source>
        <translation>La propriété &apos;%1&apos; ne peut être modifiée dans la classe &apos;%2&apos;</translation>
    </message>
</context>
<context>
    <name>Log4Qt::FileAppender</name>
    <message>
        <location filename="../log4qt/fileappender.cpp" line="131"/>
        <source>Activation of Appender &apos;%1&apos; that requires file and has no file set</source>
        <translation>L&apos;activation de &apos;Appender&apos; &apos;%1&apos; nécessite un fichier associé</translation>
    </message>
    <message>
        <location filename="../log4qt/fileappender.cpp" line="161"/>
        <source>Use of appender &apos;%1&apos; without open file</source>
        <translation>Utilisation de  &apos;Appender&apos;  &apos;%1&apos; sans fichier ouvert</translation>
    </message>
    <message>
        <location filename="../log4qt/fileappender.cpp" line="224"/>
        <source>Unable to write to file &apos;%1&apos; for appender &apos;%2&apos;</source>
        <translation>Impossible d&apos;écrire dans le fichier &apos;%1&apos; pour &apos;Appender&apos; &apos;%2&apos;</translation>
    </message>
    <message>
        <location filename="../log4qt/fileappender.cpp" line="258"/>
        <source>Unable to open file &apos;%1&apos; for appender &apos;%2&apos;</source>
        <translation>Impossible d&apos;ouvrir le fichier &apos;%1&apos; pour &apos;Appender&apos; &apos;%2&apos;</translation>
    </message>
    <message>
        <location filename="../log4qt/fileappender.cpp" line="276"/>
        <source>Unable to remove file &apos;%1&apos; for appender &apos;%2&apos;</source>
        <translation>Impossible de supprimer le fichier &apos;%1&apos; pour &apos;Appender&apos; &apos;%2&apos;</translation>
    </message>
    <message>
        <location filename="../log4qt/fileappender.cpp" line="292"/>
        <source>Unable to rename file &apos;%1&apos; to &apos;%2&apos; for appender &apos;%3&apos;</source>
        <translation>Impossible de renommer le fichier &apos;%1&apos; en &apos;%2&apos; pour &apos;Appender&apos; &apos;%3&apos;</translation>
    </message>
</context>
<context>
    <name>Log4Qt::OptionConverter</name>
    <message>
        <location filename="../log4qt/helpers/optionconverter.cpp" line="103"/>
        <source>Missing closing bracket for opening bracket at %1. Invalid subsitution in value %2.</source>
        <translation>Parenthèse fermante manquante pour la parenthèse ouvrante &apos;%1&apos;. Valeur de substitution &apos;%2&apos;  invalide</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/optionconverter.cpp" line="151"/>
        <source>Invalid option string &apos;%1&apos; for a boolean</source>
        <translation>Option chaîne &apos;%1&apos; invalide pour un booléen </translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/optionconverter.cpp" line="207"/>
        <source>Invalid option string &apos;%1&apos; for a file size</source>
        <translation>Option chaîne &apos;%1&apos; invalide pour la taille d&apos;un fichier</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/optionconverter.cpp" line="227"/>
        <source>Invalid option string &apos;%1&apos; for an integer</source>
        <translation>Option chaîne &apos;%1&apos; invalide pour un entier </translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/optionconverter.cpp" line="246"/>
        <source>Invalid option string &apos;%1&apos; for a level</source>
        <translation>Option chaîne &apos;%1&apos; invalide pour un niveau </translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/optionconverter.cpp" line="285"/>
        <source>Invalid option string &apos;%1&apos; for a target</source>
        <translation>Option chaîne &apos;%1&apos; invalide pour une cible </translation>
    </message>
</context>
<context>
    <name>Log4Qt::PatternFormatter</name>
    <message>
        <location filename="../log4qt/helpers/patternformatter.cpp" line="535"/>
        <source>Found character &apos;%1&apos; where digit was expected.</source>
        <translation>On trouve un  caractère&apos;%1&apos;, alors qu&apos;un chiffre est attendu.</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/patternformatter.cpp" line="620"/>
        <source>Option &apos;%1&apos; cannot be converted into an integer</source>
        <translation>L&apos;option &apos;%1&apos; ne peut-être convertie vers un entier</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/patternformatter.cpp" line="628"/>
        <source>Option %1 isn&apos;t a positive integer</source>
        <translation>L&apos;option &apos;%1&apos; n&apos;est pas un entier positif</translation>
    </message>
</context>
<context>
    <name>Log4Qt::PropertyConfigurator</name>
    <message>
        <location filename="../log4qt/propertyconfigurator.cpp" line="146"/>
        <source>Unable to open property file &apos;%1&apos;</source>
        <translation>Impossible d&apos;ouvrir le fichier de propriétés &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../log4qt/propertyconfigurator.cpp" line="158"/>
        <source>Unable to read property file &apos;%1&apos;</source>
        <translation>Impossible de lire le fichier de propriétés &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../log4qt/propertyconfigurator.cpp" line="370"/>
        <source>Missing appender definition for appender named &apos;%1&apos;</source>
        <translation>La définition de &apos;appender&apos; est manquente pour &apos;Appender&apos; nommé &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../log4qt/propertyconfigurator.cpp" line="380"/>
        <source>Unable to create appender of class &apos;%1&apos; named &apos;%2&apos;</source>
        <translation>La création de la classe &apos;Appender&apos;&apos;%1&apos; nommée &apos;%2&apos; est impossible</translation>
    </message>
    <message>
        <location filename="../log4qt/propertyconfigurator.cpp" line="438"/>
        <source>Unable to create layout of class &apos;%1&apos; requested by appender &apos;%2&apos;</source>
        <translation>Impossible de créer la structure de classe &apos;%1&apos; attendu par &apos;%2&apos;</translation>
    </message>
    <message>
        <source>Unable to create appender of class &apos;%1&apos; namd &apos;%2&apos;</source>
        <translation type="obsolete">La création de la classe &apos;Appender&apos;&apos;%1&apos; nommée &apos;%2&apos; est impossible</translation>
    </message>
    <message>
        <location filename="../log4qt/propertyconfigurator.cpp" line="428"/>
        <source>Missing layout definition for appender &apos;%1&apos;</source>
        <translation>La définition de la structure est manquante pour &apos;Appender&apos; &apos;%1&apos;</translation>
    </message>
    <message>
        <source>Unable to create layoput of class &apos;%1&apos; requested by appender &apos;%2&apos;</source>
        <translation type="obsolete">Impossible de créer la structure de classe &apos;%1&apos; attendu par &apos;%2&apos;</translation>
    </message>
</context>
<context>
    <name>Log4Qt::WriterAppender</name>
    <message>
        <location filename="../log4qt/writerappender.cpp" line="137"/>
        <source>Activation of Appender &apos;%1&apos; that requires writer and has no writer set</source>
        <translation>Activation de  &apos;Appender&apos;  &apos;%1&apos;  lequel nécessite un éditeur non configuré ! </translation>
    </message>
    <message>
        <location filename="../log4qt/writerappender.cpp" line="192"/>
        <source>Use of appender &apos;%1&apos; without a writer set</source>
        <translation>Utiliser &apos;Appender&apos;  &apos;%1&apos; sans éditeur configuré</translation>
    </message>
</context>
<context>
    <name>MainWindow</name>
    <message>
        <location filename="../mainwindow.ui" line="32"/>
        <source>Grbl Controller</source>
        <translation>Controleur Grbl</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="427"/>
        <source>X</source>
        <translation>X</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="622"/>
        <source>Y</source>
        <translation>Y</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="947"/>
        <source>Z</source>
        <translation>Z</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="177"/>
        <source>Send File</source>
        <translation>Envoi d&apos;un fichier</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="212"/>
        <source>Begin</source>
        <translation>Démarrer</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="185"/>
        <source>Stop</source>
        <translation>Arrêter</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="205"/>
        <source>Choose file</source>
        <translation>Choisir un fichier</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="291"/>
        <source>Runtime:</source>
        <translation>Exécution</translation>
    </message>
    <message>
        <source>Manual GCode</source>
        <translation type="obsolete">Commande directe en GCode</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="315"/>
        <source>Command</source>
        <translation>Commande</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="111"/>
        <location filename="../mainwindow.cpp" line="21"/>
        <source>Open</source>
        <translation>Ouvrir</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="980"/>
        <source>C</source>
        <translation>C</translation>
    </message>
    <message>
        <source>GRBL
settings</source>
        <translation type="obsolete">Configuratiion
GRBL</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="75"/>
        <source>Port name</source>
        <translation>Nom du port</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1643"/>
        <source>Reset Control</source>
        <translation>Commande RAZ</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1657"/>
        <source>Soft Reset Grbl</source>
        <translation>RAZ logiciel de Grbl</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1670"/>
        <source>Unlock Grbl</source>
        <translation>Débloquer Grbl</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1142"/>
        <source>Machine Coordinates</source>
        <translation>Coordonnées machine</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="517"/>
        <source>Work Coordinates</source>
        <translation>Coordonnées de travail</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="152"/>
        <source>Last State:</source>
        <translation>Dernier état</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1724"/>
        <source>Zero Position</source>
        <translation>Position zéro</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1737"/>
        <source>Go Home</source>
        <translation>Aller position repos</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1176"/>
        <source>Axis Control</source>
        <translation>Commandes d&apos;axes</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1430"/>
        <source>Z Jog</source>
        <translation>pilote Z</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1516"/>
        <source>Step Size           </source>
        <translation>Valeur du pas</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1471"/>
        <source>Absolute coordinates after adjust</source>
        <translation>Coordonnées absolues après ajustement</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1484"/>
        <source>Spindle On</source>
        <translation>Départ broche</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1382"/>
        <location filename="../mainwindow.ui" line="1392"/>
        <source>0</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1282"/>
        <source>C Jog</source>
        <translation>pilote C</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1538"/>
        <source>Visualizer</source>
        <translation>Visualisateur</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="138"/>
        <source>Baud Rate</source>
        <translation>Vitesse du port</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="251"/>
        <source>%v</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="264"/>
        <source>File progress</source>
        <translation>Avancement</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="277"/>
        <source>Queued Commands</source>
        <translation>Ordres en attente</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1631"/>
        <source>Advanced</source>
        <translation>Avancé</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1699"/>
        <source>GRBL Settings</source>
        <translation>Configuratiion
GRBL</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1744"/>
        <source>Refresh Pos</source>
        <translation>Actualiser position</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1778"/>
        <source>&amp;Help</source>
        <translation>&amp;Aide</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1784"/>
        <source>&amp;Tools</source>
        <translation>&amp;Outils</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1790"/>
        <source>&amp;File</source>
        <translation>&amp;Fichiers</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1801"/>
        <source>&amp;About</source>
        <translation>&amp;A propos</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1806"/>
        <source>&amp;Options</source>
        <translation>&amp;Options</translation>
    </message>
    <message>
        <location filename="../mainwindow.ui" line="1811"/>
        <source>E&amp;xit</source>
        <translation>&amp;Quitter</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="22"/>
        <source>Close / Reset</source>
        <translation>Fermer / Raz</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="271"/>
        <source>You appear to have upgraded to the latest version of Grbl Controller. Please be aware that as of version 3.4 the default behavior of sending commands to Grbl has been changed to send them as fast as possible (Aggressive preload mode).

Your settings have been changed to enable this mode. Why? Because it provides the most optimal use of Grbl and greatly reduces the time to finish a typical job.

What does this mean to you? Arc commands will now run smoother and faster than before, which may cause your spindle to work slightly harder, so please run some tests first. Alternately, go to the Options dialog and manually disable Aggressive Preload</source>
        <translation>Vous semblez avoir la dernière version du contrôleur Grbl. Soyez conscient que depuis la version 3.4 le comportement par défaut de l&apos;envoi de commandes à Grbl a été modifié pour les envoyer aussi vite que possible (mode de précharge agressif). 

Vos paramètres ont été modifiés pour permettre ce mode. Pourquoi? Parce qu&apos;il permet une utilisation la plus optimale de Grbl et réduit considérablement le temps de terminer un travail typique. Qu&apos;est-ce que cela signifie pour vous ? Maintenant les commandes d&apos;arc vont être plus continues et plus rapides qu&apos;auparavant, ce qui peut amener votre broche à travailler un peu plus vite, s&apos;il vous plaît donc faire quelques tests en premier. Sinon, passez à la boîte de dialogue Options et désactiver manuellement la  précharge agressive</translation>
    </message>
    <message>
        <source>Wish to &quot;zero position&quot; before beginning?</source>
        <translation type="obsolete">Voulez-vous allez en postion zéro avant de démarrer ?</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="422"/>
        <source>User clicked Port Open/Close</source>
        <translation>L&apos;utilisateur a cliqué Ouverture/Fermeture du port</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="521"/>
        <source>Resetting port to restart controller</source>
        <translation>L&apos;initilisation du port initialise le contrôleur</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="328"/>
        <source>Do you want to zero the displayed position before proceeding?</source>
        <translation>Voulez-vous afficher la postion zéro avant de démarrer ?</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="738"/>
        <source>Open File</source>
        <translation>Charger un fichier</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="740"/>
        <source>NC (*.nc);;All Files (*.*)</source>
        <translation>NC (*.nc);;Tous fichiers (*.*)</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1324"/>
        <source>Spindle On.</source>
        <translation>Marche broche</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1329"/>
        <source>Spindle Off.</source>
        <translation>Arrêt broche</translation>
    </message>
</context>
<context>
    <name>Options</name>
    <message>
        <location filename="../options.ui" line="14"/>
        <source>Options</source>
        <translation>Options</translation>
    </message>
    <message>
        <location filename="../options.ui" line="379"/>
        <source>Axis</source>
        <translation>Axes</translation>
    </message>
    <message>
        <location filename="../options.ui" line="391"/>
        <source>Invert Axis</source>
        <translation>Inverser les axes</translation>
    </message>
    <message>
        <location filename="../options.ui" line="420"/>
        <source>Z Axis</source>
        <translation>Axe Z</translation>
    </message>
    <message>
        <location filename="../options.ui" line="413"/>
        <source>Y Axis</source>
        <translation>Axe Y</translation>
    </message>
    <message>
        <location filename="../options.ui" line="406"/>
        <source>X Axis</source>
        <translation>Axe X</translation>
    </message>
    <message>
        <source>C Axis</source>
        <translation type="obsolete">Axe C</translation>
    </message>
    <message>
        <location filename="../options.ui" line="52"/>
        <source>Seconds to Wait for Response</source>
        <translation>Secondes d&apos;attente lors d&apos;une réponse</translation>
    </message>
    <message>
        <location filename="../options.ui" line="45"/>
        <source>Z-Jog Rate (inches or mm/min)</source>
        <translation>Vitesse manuelle Z  (pouces ou mmm/min)</translation>
    </message>
    <message>
        <source>Main</source>
        <translation type="obsolete">Général</translation>
    </message>
    <message>
        <location filename="../options.ui" line="109"/>
        <source>Use millimeters when sending manual commands (v0.8c+ only)</source>
        <translation>Emission des commandes manuelles en millimètre (v0.8c+ seulement)</translation>
    </message>
    <message>
        <location filename="../options.ui" line="142"/>
        <source>Filtering</source>
        <translation>Filtre</translation>
    </message>
    <message>
        <location filename="../options.ui" line="154"/>
        <source>Z Rate Limiting</source>
        <translation>Limitation de vitesse</translation>
    </message>
    <message>
        <location filename="../options.ui" line="169"/>
        <source>Limit Z Rate</source>
        <translation>Vitesse max Z</translation>
    </message>
    <message>
        <location filename="../options.ui" line="214"/>
        <source>Z-Rate Limit (inches or mm/min)</source>
        <translation>Vitesse limite Z (pouces ou mmm/min)</translation>
    </message>
    <message>
        <location filename="../options.ui" line="221"/>
        <source>XY Rate (inches or mm/min)</source>
        <translation>Vitesse XY (pouces ou mmm/min)</translation>
    </message>
    <message>
        <location filename="../options.ui" line="116"/>
        <source>Use aggressive preload strategy for Grbl</source>
        <translation>Utiliser une stratégie agressive de pré-chargement pour Grbl</translation>
    </message>
    <message>
        <location filename="../options.ui" line="30"/>
        <source>General</source>
        <translation>Général</translation>
    </message>
    <message>
        <location filename="../options.ui" line="126"/>
        <source>Wait for each jog/manual command to complete (future feature)</source>
        <translation>Attendre à chaque commande manuelle pour terminer (option future)</translation>
    </message>
    <message>
        <location filename="../options.ui" line="133"/>
        <source>Write debugging log to home folder (requires restart)</source>
        <translation>Mise au point sauvée dans le répertoire d&apos;accueil (+ redémarrage)</translation>
    </message>
    <message>
        <location filename="../options.ui" line="427"/>
        <source>Fourth Axis</source>
        <translation>4 ème axe</translation>
    </message>
    <message>
        <location filename="../options.ui" line="444"/>
        <source>Selecting the Fourth axis</source>
        <translation>Choix du quatrième axe</translation>
    </message>
    <message>
        <location filename="../options.ui" line="456"/>
        <source>A</source>
        <translation>A</translation>
    </message>
    <message>
        <location filename="../options.ui" line="472"/>
        <source>B</source>
        <translation>B</translation>
    </message>
    <message>
        <location filename="../options.ui" line="488"/>
        <source>C</source>
        <translation>C</translation>
    </message>
    <message>
        <location filename="../options.ui" line="504"/>
        <source>U</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../options.ui" line="520"/>
        <source>V</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../options.ui" line="536"/>
        <source>W</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../options.ui" line="550"/>
        <source>Enable 4-axis mode</source>
        <translation>Valider le mode 4 axes</translation>
    </message>
    <message>
        <location filename="../options.ui" line="556"/>
        <source>Display</source>
        <translation>Affichage</translation>
    </message>
    <message>
        <location filename="../options.ui" line="571"/>
        <source>Enable position request and report</source>
        <translation>Demander la position puis l&apos;afficher</translation>
    </message>
    <message>
        <location filename="../options.ui" line="578"/>
        <source>Position Request</source>
        <translation>Demande de position</translation>
    </message>
    <message>
        <location filename="../options.ui" line="593"/>
        <source>Always Request (most reliable/slightly slower jogging)</source>
        <translation>permanente (plus fiable, mais les commandes manuelles sont ralenties)</translation>
    </message>
    <message>
        <location filename="../options.ui" line="600"/>
        <source>Always Request but without Idle Check (fast jog/manual operations)</source>
        <translation>permanente mais sans controler l&apos;inactivité (commandes manuelles rapides)</translation>
    </message>
    <message>
        <location filename="../options.ui" line="607"/>
        <source>Not during manual control (no position update during jog/manual)</source>
        <translation>sauf  les commandes manuelles où l&apos;actualisation de la position est inactive.</translation>
    </message>
    <message>
        <source>Always Request</source>
        <translation type="obsolete">Demande permanente</translation>
    </message>
    <message>
        <source>Not during manual control</source>
        <translation type="obsolete">Exclure des commandes manuelles</translation>
    </message>
    <message>
        <location filename="../options.ui" line="616"/>
        <source>Request frequency (seconds)</source>
        <translation>Période des demandes (secondes)</translation>
    </message>
    <message>
        <location filename="../options.ui" line="286"/>
        <source>Command Filtering</source>
        <translation>Filtrage des commandes</translation>
    </message>
    <message>
        <location filename="../options.ui" line="298"/>
        <source>Filter file commands before sending</source>
        <translation>Filtrage des commandes du fichier GCode avant l&apos;émission</translation>
    </message>
    <message>
        <location filename="../options.ui" line="311"/>
        <source>Selectively reduce precision for excessively long lines</source>
        <translation>Réduire sélectivement la précision, lors de longues lignes de code</translation>
    </message>
    <message>
        <location filename="../options.ui" line="257"/>
        <source>Character send delay ms</source>
        <translation>Délai d&apos;émission des caractères en mS</translation>
    </message>
    <message>
        <location filename="../options.ui" line="328"/>
        <source>Grbl Line Buffer Size</source>
        <translation>Taille du tampon d&apos;entrée de Grbl</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../rs232.cpp" line="161"/>
        <source>Unexpected: Told to send %d bytes
</source>
        <translation>Inattendu : tenu d&apos;envooyer%d octets</translation>
    </message>
    <message>
        <source>Error writing to port. Write data lost!</source>
        <translation type="obsolete">Erreu d&apos;écriture sur le port. Les données à écrire sont perdues</translation>
    </message>
    <message>
        <location filename="../renderitemlist.cpp" line="156"/>
        <source> mm</source>
        <translation>mm</translation>
    </message>
    <message>
        <location filename="../renderitemlist.cpp" line="156"/>
        <source> inches</source>
        <translation>pouces</translation>
    </message>
    <message>
        <location filename="../renderitemlist.cpp" line="158"/>
        <source>  (Width-X: </source>
        <translation>  (Larg-X: </translation>
    </message>
    <message>
        <location filename="../renderitemlist.cpp" line="159"/>
        <source>  Height-Y: </source>
        <translation>  Haut-Y: </translation>
    </message>
</context>
<context>
    <name>QextSerialPort</name>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="723"/>
        <source>No Error has occurred</source>
        <translation>Aucune erreur</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="725"/>
        <source>Invalid file descriptor (port was not opened correctly)</source>
        <translation>Descripteur de périphérique invalide (port mal ouvert)</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="727"/>
        <source>Unable to allocate memory tables (POSIX)</source>
        <translation>Impossible d&apos;allouer les tables en mémoire (POSIX)</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="729"/>
        <source>Caught a non-blocked signal (POSIX)</source>
        <translation>Capture d&apos;un signal non-bloqué (POSIX)</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="731"/>
        <source>Operation timed out (POSIX)</source>
        <translation>Dépassement temporel (POSIX)</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="733"/>
        <source>The file opened by the port is not a valid device</source>
        <translation>Le fichier ouvert pour le port n&apos;est pas un périphérique valide</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="735"/>
        <source>The port detected a break condition</source>
        <translation>Le port a détecté une condition d&apos;arrêt</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="737"/>
        <source>The port detected a framing error (usually caused by incorrect baud rate settings)</source>
        <translation>Le port a détecté une erreur de trame (probablement due à une vitesse erronée)</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="739"/>
        <source>There was an I/O error while communicating with the port</source>
        <translation>Erreur d&apos;entrée/sortie lors d&apos;une commincation sur le port</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="741"/>
        <source>Character buffer overrun</source>
        <translation>Débordement du tampon de caractères</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="743"/>
        <source>Receive buffer overflow</source>
        <translation>Débordement du tampon de réception</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="745"/>
        <source>The port detected a parity error in the received data</source>
        <translation>Le port a détecté une erreur de parité lors de la réception de données</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="747"/>
        <source>Transmit buffer overflow</source>
        <translation>Débordement du tampon d&apos;émission</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="749"/>
        <source>General read operation failure</source>
        <translation>Echec d&apos;une opération de lecture</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="751"/>
        <source>General write operation failure</source>
        <translation>Echec d&apos;une opération d&apos;écriture</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="753"/>
        <source>The %1 file doesn&apos;t exists</source>
        <translation>Le fichier %1 n&apos;existe pas</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="755"/>
        <source>Permission denied</source>
        <translation>Non autorisé</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="757"/>
        <source>Device is already locked</source>
        <translation>Périphérique déjà bloqué</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="759"/>
        <source>Unknown error: %1</source>
        <translation>Erreur non répertoriée : %1</translation>
    </message>
</context>
</TS>
