<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="fr_FR">
<context>
    <name>About</name>
    <message>
        <location filename="../forms/about.ui" line="14"/>
        <source>About...</source>
        <translation>A propos ...</translation>
    </message>
    <message>
        <location filename="../forms/about.ui" line="61"/>
        <source>The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.</source>
        <translation>Le programme est fourni en l&apos;état SANS GARANTIE D&apos;AUCUNE SORTE, MEME LES GARANTIES DE CONCEPTION, MARCHANDE ET D&apos;ADAPTATION À UN USAGE PARTICULIER.</translation>
    </message>
    <message>
        <location filename="../forms/about.ui" line="84"/>
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
        <location filename="../gcode.cpp" line="47"/>
        <source>Can&apos;t open COM port </source>
        <translation>Impossible d&apos;ouvrir le port série  </translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="52"/>
        <source>-Is hardware connected to USB?</source>
        <translation>- le périphérique est-il bien connecté sur un port USB ?</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="53"/>
        <source>-Is correct port chosen?</source>
        <translation>- le port choisi est-il correct ?</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="54"/>
        <source>-Does current user have sufficient permissions?</source>
        <translation>- l&apos;utilisateur a-t-il les droits d&apos;utilisation suffisants ?</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="197"/>
        <source>SENDING: 0x%02X (CTRL-X) to check presence of Grbl
</source>
        <translation>Emis : 0x%02X (CTRL-X) pour verifier la presence de Grbl</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="200"/>
        <location filename="../gcode.cpp" line="491"/>
        <source>Sending to port failed</source>
        <translation>L&apos;émission vers le port a échouée</translation>
    </message>
    <message>
        <source>Got Grbl Version (Parsed:) %d.%d%c ($$=%d)
</source>
        <translation type="obsolete">Vous avez la version Grbl (analyse)  %d.%d%c ($$=%d)\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="393"/>
        <source>Port not available yet</source>
        <translation>Le port n&apos;est plus disponible</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="456"/>
        <source>Buffer size too small</source>
        <translation>Le tampon est trop petit</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="466"/>
        <source>SENDING[%d]: 0x%02X (CTRL-X)
</source>
        <translation>EMIS[%d]: 0x%02X (CTRL-X)\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="468"/>
        <source>SENDING[%d]: %s
</source>
        <translation>EMIS[%d]: %s\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="502"/>
        <source>WAITFOROK FAILED
</source>
        <translation>Echec lors de l&apos;attente de Ok </translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="508"/>
        <source>Wait for ok failed</source>
        <translation>L&apos;attente d&apos;un bon déroulement a échouée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="627"/>
        <location filename="../gcode.cpp" line="845"/>
        <source>Error reading data from COM port
</source>
        <translation>Erreur de lecture des données sur le port série</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="649"/>
        <source>Unexpected: list is empty (o)!</source>
        <translation>Liste attendue vide (o) </translation>
    </message>
    <message>
        <source>GOT[%d]:%s for %s
</source>
        <translation type="obsolete">Obtenu [%d]:%s pour %s\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="666"/>
        <source>Error?</source>
        <translation>Erreur non répertoriée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="668"/>
        <source>Unexpected: list is empty (e)!</source>
        <translation>Liste attendue vide (e) </translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="727"/>
        <location filename="../gcode.cpp" line="856"/>
        <source>GOT:%s
</source>
        <translation>Obtenu : %s\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="795"/>
        <source>Wait interrupted by user</source>
        <translation>Attente d&apos;interuption par l&apos;utilisateur</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="864"/>
        <source>Expecting Grbl version string. Unable to parse response.</source>
        <translation>Attente de la version Grbl, impossible d&apos;analyser la réponse</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="888"/>
        <source>No data from COM port after connect. Expecting Grbl version string.</source>
        <translation>Aucune données depuis le port série après la connexion, en attente de la version Grbl</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="909"/>
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
        <source>Decoded: State:%s MPos: %f,%f,%f WPos: %f,%f,%f
</source>
        <translation type="obsolete">Décodage : Etat :%s MPos: %f,%f,%f WPos: %f,%f,%f
</translation>
    </message>
    <message>
        <source>Decoded: State:%s MPos: %f,%f,%f,%f WPos: %f,%f,%f,%f
</source>
        <translation type="obsolete">Décodage : Etat :%s MPos: %f,%f,%f,%f WPos: %f,%f,%f,%f
</translation>
    </message>
    <message>
        <source>Error decoding position data!
</source>
        <translation type="obsolete">Erreur de décodage des données de position\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="371"/>
        <source>Got Grbl Version (Parsed:) %d.%d%c%c ($$=%d)
</source>
        <translation>Vous avez la version Grbl (analyse)  %d.%d%c ($$=%d)\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="654"/>
        <location filename="../gcode.cpp" line="673"/>
        <source>GOT[%d]: &apos;%s&apos; for &apos;%s&apos; (aggressive)
</source>
        <translation>Obtenu :[%d]: &apos;%s&apos; pour &apos;%s&apos; (offensif)</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="688"/>
        <source>GOT: &apos;%s&apos; (aggressive)
</source>
        <translation>Obtenu : &apos;%s&apos; (offensif)</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1018"/>
        <source>Incorrect - extra axis present in hardware but options set for only 3 axes. Please fix options.</source>
        <translation>L&apos;axe supplémentaire existe matériellement. Veuillez corriger les options en cochant 4 ème axe.</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1027"/>
        <source>Incorrect - extra axis not present in hardware but options set for &gt; 3 axes. Please fix options.</source>
        <translation>L&apos;axe supplémentaire n&apos;existe pas matériellement. Veuillez corriger les options  en décochant 4 ème axe.</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1059"/>
        <source>Decoded: State:%s</source>
        <translation>Decodage : Etat :%s</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1061"/>
        <source>Decoded: MPos: %f,%f,%f WPos: %f,%f,%f
</source>
        <translation>Decodage : MPos: %f,%f,%f,%f WPos: %f,%f,%f,%f
</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1066"/>
        <source>Decoded: MPos: %f,%f,%f,%f WPos: %f,%f,%f,%f
</source>
        <translation>Decodage : MPos: %f,%f,%f,%f WPos: %f,%f,%f,%f
</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1125"/>
        <source>GOT-TE:%s
</source>
        <translation>Obtenu evenement temporel :%s\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1147"/>
        <source>Sending file &apos;%1&apos;</source>
        <translation>Emission du fichier &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1308"/>
        <source>Gave up waiting for OK
</source>
        <translation>Fin d&apos;attente Ok\n</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1328"/>
        <source>Code sent successfully with %1 error(s):</source>
        <translation>Code émis correctement avec %1 erreur(s)</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1340"/>
        <source>Code sent successfully with no errors.</source>
        <translation>Code émis correctement sans erreur</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1347"/>
        <source>Filtered %1 commands:</source>
        <translation>Commande filtrée %1</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1360"/>
        <source>Process interrupted.</source>
        <translation>Processus interrompu</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1394"/>
        <source>Removed unsupported command &apos;%1&apos; part of &apos;%2&apos;</source>
        <translation>Suppression de la commande &apos;%1&apos; portion de &apos;%2 ( non supportée)</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1410"/>
        <source>Removed unsupported G command &apos;%1&apos;</source>
        <translation>Suppression de la commande G  &apos;%1&apos;  non supportée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1423"/>
        <source>Removed unsupported M command &apos;%1&apos;</source>
        <translation>Suppression de la commande M  &apos;%1&apos;  non supportée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1443"/>
        <source>Removed unsupported command &apos;%1&apos;</source>
        <translation>Suppression de la commande &apos;%1&apos;  non supportée</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1577"/>
        <source>Unable to remove enough decimal places for command (will be truncated): %s</source>
        <translation>Impossible de supprimer assez de decimales pour la commande (sera tronquee) %s</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1581"/>
        <source>Error, insufficent reduction &apos;%1&apos;</source>
        <translation>Erreur : réduction insuffisante  &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1583"/>
        <source>Precision reduced &apos;%1&apos;</source>
        <translation>Précision réduite  &apos;%1&apos;</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1780"/>
        <source>Z-Rate Limit: [%1]=&gt;[%2]</source>
        <translation>Limite de vitesse Z  [%1]=&gt;[%2]</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1785"/>
        <source>Z-Rate Limit: [%1]=&gt;[%2,%3]</source>
        <translation>Limite de vitesse Z :  [%1]=&gt;[%2,%3]</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1830"/>
        <source>XY-Rate Limit FIX: [%1]=&gt;[%2]</source>
        <translation>Correction de la limite de vitesse XY : [%1]=&gt;[%2]</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="1889"/>
        <source>Bad command: %1</source>
        <translation>Commande erronee : %1</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="2000"/>
        <source>Options specify use mm but Grbl parser set for inches. Fixing.</source>
        <translation>Vous utiliser des &apos;mm&apos; alors que l&apos;analyse indique des &apos;pouces&apos;.  Corriger dans la configuration</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="2005"/>
        <source>Options specify use inches but Grbl parser set for mm. Fixing.</source>
        <translation>Vous utiliser les &apos;pouces&apos; alors que l&apos;analyse indique des &apos;mm&apos;. Corriger dans la configuration</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="2021"/>
        <source>Options specify use mm but Grbl reporting set for inches. Fixing.</source>
        <translation>Vous utiliser les mm alors que Grbl donne des pouces. Corriger dans la configuration</translation>
    </message>
    <message>
        <location filename="../gcode.cpp" line="2026"/>
        <source>Options specify use inches but Grbl reporting set for mm. Fixing.</source>
        <translation>Vous utiliser les &apos;pouce&apos;s alors que Grbl donne des &apos;mm&apos;. Corriger dans la configuration</translation>
    </message>
    <message>
        <source>(mm)</source>
        <translation type="obsolete">(mm)</translation>
    </message>
    <message>
        <source>(in)</source>
        <translation type="obsolete">(pouce)</translation>
    </message>
</context>
<context>
    <name>GrblDialog</name>
    <message>
        <location filename="../forms/grbldialog.ui" line="20"/>
        <source>Grbl Settings</source>
        <translation>Configuration GRBL</translation>
    </message>
    <message>
        <location filename="../forms/grbldialog.ui" line="68"/>
        <source>Apply</source>
        <translation>Appliquer</translation>
    </message>
    <message>
        <location filename="../forms/grbldialog.ui" line="75"/>
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
        <location filename="../log4qt/helpers/factory.cpp" line="261"/>
        <source>Cannot convert to type &apos;%1&apos; for property &apos;%2&apos; on object of class &apos;%3&apos;</source>
        <translation>La conversion de type &apos;%1&apos; de la propriété &apos;%2&apos; de l&apos;objet de classe &apos;%3&apos; est impossible.</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="374"/>
        <source>Unable to set property value on object</source>
        <translation>Impossible d&apos;inialiser la valeur de la propriété de l&apos;objet.</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="380"/>
        <source>Invalid null object pointer</source>
        <translation>Pointeur d&apos;objet &apos;null&apos; invalide</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="389"/>
        <source>Invalid empty property name</source>
        <translation>Nom de propriété invalide (vide)</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="407"/>
        <source>Property &apos;%1&apos; does not exist in class &apos;%2&apos;</source>
        <translation>La propriété &apos;%1&apos; n&apos;existe pas dans la classe &apos;%2&apos;</translation>
    </message>
    <message>
        <location filename="../log4qt/helpers/factory.cpp" line="420"/>
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
        <location filename="../forms/mainwindow.ui" line="32"/>
        <source>Grbl Controller</source>
        <translation>Contrôleur Grbl</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="72"/>
        <source>attempts to connect to the card containing &apos;Grbl&apos; or terminates the connection</source>
        <translation>Essai de connexion à la carte contenant &apos;Grbl&apos; ou arréter la connexion</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="126"/>
        <source>Port selection in those detected by the system</source>
        <translation>Sélection du port détecté par le système</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="158"/>
        <source>connection speed to card (bauds)</source>
        <translation>Vitesse de connexion à la carte (bauds)</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="180"/>
        <source>stops sending the contents of the file &apos;Gcode&apos;</source>
        <translation>Arréter l&apos;émission du contenu du fichier &apos;Gcode&apos;</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="203"/>
        <source>load a file for animation or send to Grbl</source>
        <translation>Chager un fichier &apos;Gcode&apos; pour animation ou émission vers &apos;Grbl&apos;</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="213"/>
        <source>sending line by line the contents of the file &apos;Gcode&apos;</source>
        <translation>Emet ligne par ligne le cotenu du fichier (Gcode&apos;</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="223"/>
        <source>shows the full name of the loaded file</source>
        <translation>Montre le nom complet du fichier chargé</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="230"/>
        <source>commands are sent to &apos;Grbl&apos; simply control without executing</source>
        <translation>Les commandes sontsimplement  transmise à &apos;Grbl&apos;pour vérification sans exécution</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="233"/>
        <location filename="../mainwindow.cpp" line="2122"/>
        <source>Check</source>
        <translation>Vérifier</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="334"/>
        <source>time to send a file to &apos;Grbl&apos;</source>
        <translation>Durée pour envoyer un fichier vers &apos;Grbl&apos;</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="337"/>
        <source>00:00:00</source>
        <translation>00:00:00</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="382"/>
        <source>indicates the last release state Grbl</source>
        <translation>Indique le dernier état de Grbl</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="385"/>
        <source>no state</source>
        <translation>Acun état</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="405"/>
        <source>Lines:</source>
        <translation>Lignes</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="476"/>
        <source>Console</source>
        <translation>Console</translation>
    </message>
    <message>
        <source>Gcode</source>
        <translation type="obsolete">Gcode</translation>
    </message>
    <message>
        <source>Simulate</source>
        <translation type="obsolete">Simulation</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="2197"/>
        <source>Pause</source>
        <translation>Pause</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="834"/>
        <source>Line :</source>
        <translation>Ligne</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1048"/>
        <source>Speed rate</source>
        <translation>Vitesse de travail</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1103"/>
        <source>Speed rate gcode (mm or inches per minute)</source>
        <translation>Vitesse de travail gcode (mm ou pouces par minute)</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1169"/>
        <source>Spindle control: running -&gt; yellow</source>
        <translation>Commande de broche : fonctionne -&gt; jaune</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1300"/>
        <source>Pass in absolute coordinates after moving it occurs in relative displacement</source>
        <translation>Passe en coordonnées absolues après les commandes manuelles qui sont en déplacement relatif</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1303"/>
        <source>G90 after adjust</source>
        <translation>G90 après l&apos;ajustement</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1338"/>
        <source>X</source>
        <translation>X</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1439"/>
        <source>Unit X axis</source>
        <translation>Unité de l&apos;axe X</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1592"/>
        <source>Y</source>
        <translation>Y</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1692"/>
        <source>Unit Y axis</source>
        <translation>Unité de l&apos;axe Y</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1844"/>
        <source>Z</source>
        <translation>Z</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="172"/>
        <source>Send File</source>
        <translation>Envoi d&apos;un fichier</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="216"/>
        <source>Begin</source>
        <translation>Démarrer</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="183"/>
        <source>Stop</source>
        <translation>Arrêter</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="206"/>
        <source>Choose file</source>
        <translation>Choisir un fichier</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="318"/>
        <source>Runtime:</source>
        <translation>Exécution</translation>
    </message>
    <message>
        <source>Manual GCode</source>
        <translation type="obsolete">Commande directe en GCode</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="438"/>
        <source>Command</source>
        <translation>Commande</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="75"/>
        <location filename="../mainwindow.cpp" line="20"/>
        <source>Open</source>
        <translation>Ouvrir</translation>
    </message>
    <message>
        <source>C</source>
        <translation type="obsolete">C</translation>
    </message>
    <message>
        <source>GRBL
settings</source>
        <translation type="obsolete">Configuratiion
GRBL</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="107"/>
        <source>Port name</source>
        <translation>Nom du port</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="505"/>
        <source>Visual</source>
        <translation>Visuel</translation>
    </message>
    <message>
        <source>animation of the scene</source>
        <translation type="obsolete">Animation de la scène 3D</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="543"/>
        <location filename="../mainwindow.cpp" line="2150"/>
        <source>Animate</source>
        <translation>Animation</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="561"/>
        <source>Starting and stopping the animation</source>
        <translation>Démarre et arrête l&apos;animation 3D</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="623"/>
        <location filename="../forms/mainwindow.ui" line="663"/>
        <source>interpolation tolerance for viewer 3D</source>
        <translation>Tolérance d&apos;interpolation du visualisateur 3D</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="697"/>
        <location filename="../forms/mainwindow.ui" line="1442"/>
        <location filename="../forms/mainwindow.ui" line="1695"/>
        <location filename="../forms/mainwindow.ui" line="1947"/>
        <location filename="../mainwindow.cpp" line="2260"/>
        <location filename="../mainwindow.cpp" line="2295"/>
        <source>mm</source>
        <translation>mm</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="715"/>
        <source>Arc segments</source>
        <translatorcomment>Segments d&apos;arc</translatorcomment>
        <translation></translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="771"/>
        <source>interpolation number of segments for 3D</source>
        <translation>Nombre de segment d&apos;interpolation pour la 3D</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="803"/>
        <source>Up one line in the gcode</source>
        <translation>Remonte d&apos;une ligne dans le Gcode</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="847"/>
        <source>Current line gcode</source>
        <translation>Ligne courante du Gcode</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="865"/>
        <source>Down one line in the gcode</source>
        <translation>Descend d&apos;une ligne dans le Gcode</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="915"/>
        <source>Animation period mS</source>
        <translation>Période de l&apos;animation en mS</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="967"/>
        <source>Period mS</source>
        <translation>Période mS</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="992"/>
        <source>Value of the period</source>
        <translation>Valeur de la période</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="519"/>
        <source>Monitoring the progress of the animation gcode</source>
        <translation>Montre l&apos;avancement de l&apos;animation du Gcode</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="540"/>
        <source>animation of the scene 3D</source>
        <translation>Animation de la scène en 3D</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1944"/>
        <source>Unit Z axis</source>
        <translation>Unité de l&apos;axe Z</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2270"/>
        <source>Unit of the fourth axis</source>
        <translation>Unité du quatrième axe</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2273"/>
        <source>deg</source>
        <translation>deg</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2248"/>
        <source>T</source>
        <translation>T
</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1140"/>
        <source>mm/mn</source>
        <translation>mm/mn</translation>
    </message>
    <message>
        <source>Speed gcode mm per minute</source>
        <translation type="obsolete">Vitesse de travail du Gcode &apos;mm&apos; par minute</translation>
    </message>
    <message>
        <source>Segments</source>
        <translation type="obsolete">Segments</translation>
    </message>
    <message>
        <source>Speed gcode (mm or inches per minute)</source>
        <translation type="obsolete">Vitesse d&apos;avance du gcode (mm ou pouces par minutes)</translation>
    </message>
    <message>
        <source>Step Size</source>
        <translation type="obsolete">Valeur du pas</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2847"/>
        <source>T Jog</source>
        <translation>Commande T</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3178"/>
        <source>Reset Control</source>
        <translation>Commande RAZ</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3192"/>
        <source>Soft Reset Grbl</source>
        <translation>RAZ logiciel de Grbl</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3205"/>
        <source>Unlock Grbl</source>
        <translation>Débloquer Grbl</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1260"/>
        <source>Machine Coordinates</source>
        <translation>Coordonnées machine</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1280"/>
        <source>Work Coordinates</source>
        <translation>Coordonnées de travail</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="363"/>
        <source>Last State:</source>
        <translation>Dernier état</translation>
    </message>
    <message>
        <source>interpolation number of segments</source>
        <translation type="obsolete">Nombre de segments d&apos;interpolation</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="648"/>
        <source>Tolerance</source>
        <translation>Tolérance</translation>
    </message>
    <message>
        <source>interpolation tolerance</source>
        <translation type="obsolete">Tolérance d&apos;interpolation</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3468"/>
        <source>tool selection</source>
        <translation>Choix de l&apos;outil</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3493"/>
        <source>With or without bounding box</source>
        <translation>Visualisation ou non de l&apos;enveloppe</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3496"/>
        <source>Bbox</source>
        <translation>Eboite</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3506"/>
        <source>with or without rapid movements</source>
        <translation>Visualise ou non les mouvements rapides</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3576"/>
        <source>Zero Position</source>
        <translation>= Position zéro</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3589"/>
        <source>Go Home</source>
        <translation>Aller position repos</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2706"/>
        <source>Axis Control</source>
        <translation>Commandes d&apos;axes</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2466"/>
        <source>Step size, accept cursors keyboard commands</source>
        <translation>Valeur du pas, accepte les commandes des curseurs clavier</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2582"/>
        <source>Small movements of the Z axis</source>
        <translation>Petits déplcements de l&apos;axe Z</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2678"/>
        <source>Step value for the relative movements (G91)</source>
        <translation>Valeur du pas pour les déplacements relatifs</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="2965"/>
        <location filename="../mainwindow.cpp" line="1500"/>
        <source>Z Jog</source>
        <translation>pilote Z</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3051"/>
        <source>Step Size           </source>
        <translation>Valeur du pas</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3006"/>
        <source>Absolute coordinates after adjust</source>
        <translation>Coordonnées absolues après ajustement</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="1172"/>
        <location filename="../forms/mainwindow.ui" line="3019"/>
        <location filename="../mainwindow.cpp" line="1788"/>
        <source>Spindle On</source>
        <translation>Départ broche</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="421"/>
        <location filename="../forms/mainwindow.ui" line="850"/>
        <location filename="../forms/mainwindow.ui" line="2502"/>
        <location filename="../forms/mainwindow.ui" line="2610"/>
        <location filename="../forms/mainwindow.ui" line="2911"/>
        <location filename="../forms/mainwindow.ui" line="2921"/>
        <source>0</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1511"/>
        <source>C Jog</source>
        <translation>pilote C</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3073"/>
        <source>Visualizer</source>
        <translation>Visualisateur</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="145"/>
        <source>Baud Rate</source>
        <translation>Vitesse du port</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="272"/>
        <source>%v</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="285"/>
        <source>File progress</source>
        <translation>Avancement</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="298"/>
        <source>Queued Commands</source>
        <translation>Ordres en attente</translation>
    </message>
    <message>
        <source>Lines</source>
        <translation type="obsolete">Lignes</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3166"/>
        <source>Advanced</source>
        <translation>Avancé</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3234"/>
        <source>GRBL Settings</source>
        <translation>Configuratiion
GRBL</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3240"/>
        <source>Viewer3D</source>
        <translation>Visu 3D</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3340"/>
        <source>Perspective view</source>
        <translation>Vue en perspective</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3357"/>
        <source>Front view</source>
        <translation>Vue de face</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3371"/>
        <source>Back view</source>
        <translation>Vue arrière</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3385"/>
        <source>Left view</source>
        <translation>Vue de gauche</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3399"/>
        <source>Right view </source>
        <translation>Vue de droite</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3413"/>
        <source>Bottom view</source>
        <translation>Vue de dessous</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3427"/>
        <source>Top view</source>
        <translation>Vue de dessus</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3441"/>
        <source>Vector up along Y axis </source>
        <translation>Veceur d&apos;alignement vertical selon l&apos;axe Y</translation>
    </message>
    <message>
        <source>With or not tool</source>
        <translation type="obsolete">Avec ou sans outil</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3474"/>
        <source>Tool</source>
        <translation>Outil</translation>
    </message>
    <message>
        <source>With or not boubing box</source>
        <translation type="obsolete">Avec ous sans la boite enveloppante</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3509"/>
        <source>G0</source>
        <translation>G0</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3541"/>
        <location filename="../forms/mainwindow.ui" line="3544"/>
        <source>Help 3D</source>
        <translation>Aide 3D</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3596"/>
        <source>Refresh Pos</source>
        <translation>Actualiser position</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3616"/>
        <source>Firmware :</source>
        <translation>Micrologiciel :</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3632"/>
        <location filename="../mainwindow.cpp" line="698"/>
        <source>none</source>
        <translation>aucun</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3653"/>
        <source>&amp;Help</source>
        <translation>&amp;Aide</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3659"/>
        <source>&amp;Tools</source>
        <translation>&amp;Outils</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3665"/>
        <source>&amp;File</source>
        <translation>&amp;Fichiers</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3676"/>
        <source>&amp;About</source>
        <translation>&amp;A propos</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3681"/>
        <source>&amp;Options</source>
        <translation>&amp;Options</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="3686"/>
        <source>E&amp;xit</source>
        <translation>&amp;Quitter</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="21"/>
        <source>Close / Reset</source>
        <translation>Fermer / Raz</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="351"/>
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
        <location filename="../mainwindow.cpp" line="612"/>
        <source>User clicked Port Open/Close</source>
        <translation>L&apos;utilisateur a clique Ouverture/Fermeture du port</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="758"/>
        <source>Resetting port to restart controller</source>
        <translation>L&apos;initialisation du port initialise le contrôleur</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="479"/>
        <source>Do you want to zero the displayed position before proceeding?</source>
        <translation>Voulez-vous afficher la postion zéro avant de démarrer ?</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="50"/>
        <source>%s has started</source>
        <translation>Lancement de %s</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="370"/>
        <source>No tool</source>
        <translation>Sans outil</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="372"/>
        <source>Mini 1 mm</source>
        <translation>Mini 1mm</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="374"/>
        <source>Hemi 3 mm</source>
        <translation>Hémi 3mm</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="376"/>
        <source>Right 3 mm</source>
        <translation>Droit 3mm</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="378"/>
        <source>Sharp 3 mm</source>
        <translation>Pointu 3mm</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="380"/>
        <source>Short 3 mm</source>
        <translation>Court 3 mm</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="419"/>
        <source>%s has stopped</source>
        <translation>Fin de %s</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="985"/>
        <source>Open File</source>
        <translation>Charger un fichier</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="987"/>
        <source>NC (*.nc);;All Files (*.*)</source>
        <translation>NC (*.nc);;Tous fichiers (*.*)</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1503"/>
        <source>A Jog</source>
        <translation>pilote A</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1507"/>
        <source>B Jog</source>
        <translation>pilote B</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1515"/>
        <source>U Jog</source>
        <translation>pilote U</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1519"/>
        <source>V Jog</source>
        <translation>pilote V</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1523"/>
        <source>W Jog</source>
        <translation>pilote W</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1788"/>
        <source>Spindle Off</source>
        <translation>Arrêt broche</translation>
    </message>
    <message>
        <source>Spindle On.</source>
        <translation type="obsolete">Marche de la  broche</translation>
    </message>
    <message>
        <source>Spindle Off.</source>
        <translation type="obsolete">Arrêt de la broche</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1939"/>
        <source>Usr chg: pos=%d new=%d
</source>
        <translation>Changement de position : %d -&gt; =%d</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1941"/>
        <source>Usr chg: pos=%.1f new=%.1f
</source>
        <translation>Changement de position : %.1f -&gt; =%.1f</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1948"/>
        <source>Usr chg no slider: %d
</source>
        <translation>Utilisation du coulisseau :  %d</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1950"/>
        <source>Usr chg no slider: %.1f
</source>
        <translation>Utilisation du coulisseau :  %.1f</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1959"/>
        <source>Pressed and stopped
</source>
        <translation>Actionne et stoppe</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1964"/>
        <source>Pressed not stopped
</source>
        <translation>Actionne sans stop</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="1970"/>
        <source>Released
</source>
        <translation>Relache</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="2120"/>
        <source>No check</source>
        <translation>Fin vérifier</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="2148"/>
        <source>No animate</source>
        <translation>Fin animation</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="2276"/>
        <source>in</source>
        <translation>pou</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="2285"/>
        <source>mn</source>
        <translation>mm</translation>
    </message>
    <message>
        <location filename="../mainwindow.cpp" line="2293"/>
        <source>deg.</source>
        <translation>deg</translation>
    </message>
    <message>
        <location filename="../forms/mainwindow.ui" line="564"/>
        <location filename="../mainwindow.cpp" line="2191"/>
        <source>Run</source>
        <translation>Marche</translation>
    </message>
</context>
<context>
    <name>Options</name>
    <message>
        <location filename="../forms/options.ui" line="20"/>
        <source>Options</source>
        <translation>Options</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="450"/>
        <source>Axis</source>
        <translation>Axes</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="462"/>
        <source>Invert Axis</source>
        <translation>Inverser les axes</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="491"/>
        <source>Z Axis</source>
        <translation>Axe Z</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="484"/>
        <source>Y Axis</source>
        <translation>Axe Y</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="477"/>
        <source>X Axis</source>
        <translation>Axe X</translation>
    </message>
    <message>
        <source>C Axis</source>
        <translation type="obsolete">Axe C</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="64"/>
        <source>Seconds to Wait for Response</source>
        <translation>Secondes d&apos;attente lors d&apos;une réponse</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="57"/>
        <source>Z-Jog Rate (inches or mm/min)</source>
        <translation>Vitesse manuelle Z  (pouces ou mmm/min)</translation>
    </message>
    <message>
        <source>Main</source>
        <translation type="obsolete">Général</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="180"/>
        <source>Use millimeters when sending manual commands (v0.8c+ only)</source>
        <translation>Emission des commandes manuelles en millimètre (v0.8c+ seulement)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="213"/>
        <source>Filtering</source>
        <translation>Filtre</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="225"/>
        <source>Z Rate Limiting</source>
        <translation>Limitation de vitesse</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="240"/>
        <source>Limit Z Rate</source>
        <translation>Vitesse max Z</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="285"/>
        <source>Z-Rate Limit (inches or mm/min)</source>
        <translation>Vitesse limite Z (pouces ou mmm/min)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="292"/>
        <source>XY Rate (inches or mm/min)</source>
        <translation>Vitesse XY (pouces ou mmm/min)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="187"/>
        <source>Use aggressive preload strategy for Grbl</source>
        <translation>Utiliser une stratégie offensive de pré-chargement pour Grbl</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="42"/>
        <source>General</source>
        <translation>Général</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="122"/>
        <source>Max Log Lines ( 0 : unlimited )</source>
        <translation>Max Lignes Jornal (0: illimité)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="197"/>
        <source>Wait for each jog/manual command to complete (future feature)</source>
        <translation>Attendre à chaque commande manuelle pour terminer (option future)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="204"/>
        <source>Write debugging log to home folder (requires restart)</source>
        <translation>Mise au point sauvée dans le répertoire d&apos;accueil (+ redémarrage)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="498"/>
        <source>Fourth Axis</source>
        <translation>4 ème axe</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="515"/>
        <source>Selecting the Fourth axis</source>
        <translation>Choix du quatrième axe</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="527"/>
        <source>A</source>
        <translation>A</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="543"/>
        <source>B</source>
        <translation>B</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="559"/>
        <source>C</source>
        <translation>C</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="575"/>
        <source>U</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="591"/>
        <source>V</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="607"/>
        <source>W</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="621"/>
        <source>Enable 4-axis mode</source>
        <translation>Valider le mode 4 axes</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="627"/>
        <source>Display</source>
        <translation>Affichage</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="792"/>
        <source>Display the position</source>
        <translation>Affiche la position</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="828"/>
        <source>Enable position request and report</source>
        <translation>Demander la position puis l&apos;afficher</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="847"/>
        <source>Synchronous simulation (! EXPERIMENTAL !)</source>
        <translation>Simulation synchrone (!! EXPERIMENTAL !!</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="869"/>
        <source>No display</source>
        <translation>Sans affichage</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="645"/>
        <source>Position Request</source>
        <translation>Demande de position</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="666"/>
        <source>Always Request (most reliable/slightly slower jogging)</source>
        <translation>permanente (plus fiable, mais les commandes manuelles sont ralenties)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="682"/>
        <source>Always Request but without Idle Check (fast jog/manual operations)</source>
        <translation>permanente mais sans controler l&apos;inactivité (commandes manuelles rapides)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="698"/>
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
        <location filename="../forms/options.ui" line="719"/>
        <source>Request frequency (seconds)</source>
        <translation>Période des demandes (secondes)</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="357"/>
        <source>Command Filtering</source>
        <translation>Filtrage des commandes</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="369"/>
        <source>Filter file commands before sending</source>
        <translation>Filtrage des commandes du fichier GCode avant l&apos;émission</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="382"/>
        <source>Selectively reduce precision for excessively long lines</source>
        <translation>Réduire sélectivement la précision, lors de longues lignes de code</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="328"/>
        <source>Character send delay ms</source>
        <translation>Délai d&apos;émission des caractères en mS</translation>
    </message>
    <message>
        <location filename="../forms/options.ui" line="399"/>
        <source>Grbl Line Buffer Size</source>
        <translation>Taille du tampon d&apos;entrée de Grbl</translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../rs232.cpp" line="160"/>
        <source>Unexpected: Told to send %d bytes
</source>
        <translation>Inattendu : impossible d&apos;envoyer%d octets</translation>
    </message>
    <message>
        <source>Unable to write bytes to port probably due to outgoing queue full. Write data lost!</source>
        <translation type="obsolete">Impossible d&apos;ecrire sur le port, probablement la file d&apos;attente de sortie est pleine.Perte de donnees en ecriture !</translation>
    </message>
    <message>
        <source>Error writing to port. Write data lost!</source>
        <translation type="obsolete">Erreu d&apos;ecriture sur le port. Les donnees a ecrire sont perdues</translation>
    </message>
    <message>
        <location filename="../renderitemlist.cpp" line="155"/>
        <source> mm</source>
        <translation>mm</translation>
    </message>
    <message>
        <location filename="../renderitemlist.cpp" line="155"/>
        <source> inches</source>
        <translation>pouces</translation>
    </message>
    <message>
        <location filename="../renderitemlist.cpp" line="157"/>
        <source>  (Width-X: </source>
        <translation>  (Larg-X: </translation>
    </message>
    <message>
        <location filename="../renderitemlist.cpp" line="158"/>
        <source>  Height-Y: </source>
        <translation>  Haut-Y: </translation>
    </message>
    <message>
        <source>Unexpected type %c</source>
        <translation type="obsolete">Type attendu %c</translation>
    </message>
    <message>
        <location filename="../log4qt/logmanager.cpp" line="311"/>
        <source>Initialising Log4Qt %1</source>
        <translation>Initialisation de LOg4Qt %1</translation>
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
        <translation>Erreur d&apos;entrée/sortie lors d&apos;une communication sur le port</translation>
    </message>
    <message>
        <location filename="../QextSerialPort/qextserialport.cpp" line="741"/>
        <source>Character buffer overrun</source>
        <translation>Dépassementt du tampon de caractères</translation>
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
<context>
    <name>Viewer</name>
    <message>
        <location filename="../visu3D/viewer3D.cpp" line="353"/>
        <source>&lt;h3&gt;Version %1&lt;/h3&gt;</source>
        <translation>&lt;h3&gt;Version %1&lt;/h3&gt;</translation>
    </message>
    <message>
        <location filename="../visu3D/viewer3D.cpp" line="354"/>
        <source>&lt;code&gt;by LETARTARE  %1&lt;/code&gt;</source>
        <translation>&lt;code&gt;par LETARTARE  %1&lt;/code&gt;</translation>
    </message>
    <message>
        <location filename="../visu3D/viewer3D.cpp" line="355"/>
        <source>&lt;br&gt;&lt;br&gt; for  &lt;h2&gt; %1&lt;/h2&gt;</source>
        <translation>&lt;br&gt;&lt;br&gt; pour  &lt;h2&gt; %1&lt;/h2&gt;</translation>
    </message>
    <message>
        <location filename="../visu3D/viewer3D.cpp" line="358"/>
        <source>&lt;br&gt;Displays the &lt;b&gt;Path&lt;/b&gt; GCode using &apos;OpenGL&apos;.</source>
        <translation>&lt;br&gt;Montre les &lt;b&gt;Chemins&lt;/b&gt; GCodeen utilisant &apos;OpenGL&apos;.</translation>
    </message>
    <message>
        <location filename="../visu3D/viewer3D.cpp" line="359"/>
        <source>&lt;br&gt;&lt;br&gt;&lt;i&gt;Move the camera using the mouse.&lt;/i&gt;</source>
        <translation>&lt;br&gt;&lt;br&gt;&lt;i&gt;Déplacer la caméra grace à la souris.&lt;/i&gt;</translation>
    </message>
</context>
</TS>
