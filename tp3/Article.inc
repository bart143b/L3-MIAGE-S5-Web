<?php
/**
 * PHP version 5 ou plus
 *
 * @category   L3 Web Persistance
 * @package    web.tp3
 * @author     Isabelle Mirbel <Isabelle.Mirbel@unice.fr>
 * @author     Adam Issoufi <issoufi.adam1@gmail.com>
 * @version    1.0
 * @link       http://www-mips.unice.fr/~ai401938/web/tp3
 */
 
class Article {
	
	/**
	 * Catégorie de l'article
	 * @var Categorie
	 */
	private $categorie ; 
	
	/**
	 * Titre de l'artcile
	 * @var string
	 */
	private $titre;

	/**
	 * L'auteur de l'article
	 * @var string
	 */
	private $auteur;

	/**
	 * Le contenu de l'article
	 * @var string
	 */
	private $texte;
	
	/**
	 * constructeur
	 * @param string $titre
	 * @param string $auteur
	 * @param string $texte
	 */
	public function Article($titre = "", $auteur="", $texte="") {
		$this->auteur = $auteur;
		$this->texte = $texte;
		$this->titre = $titre;
	}
	

	/**
	 * retourne la catégorie, si elle existe, de l'article
	 * @return Categorie
	 */
	public function getCategorie()
	{
		return $this->categorie;
	}
	
	/**
	 * pour affecter ou changer de catégorie
	 * @param Categorie $cat
	 */
	public function setCategorie(Categorie $cat)
	{
		$this->categorie = $cat;
	}
	
	
	
	/**
	 * retourne le titre de l'article
	 * @return string
	 */
	public function getTitre()
	{
		return $this->titre;
	}

	/**
	 * retourne l'auteur de l'article
	 * @return string
	 */
	public function getAuteur()
	{
		return $this->auteur;
	}

	/**
	 * retourne le contenu de l'article
	 * @return string
	 */
	public function getTexte()
	{
		return $this->texte;
	}
	
	/**
	 * pour affecter ou changer de titre
	 * @param string $titre
	 */
	public function setTitre($titre)
	{
		$this->titre = titre;
	}
	
	
	/**
	 * pour obtenir une vue html de l'article
	 */
	public function getHtml()
	{
		$result = <<<EOR
		<fieldset>
			<legend>{$this->titre} par {$this->auteur}</legend>
			{$this->texte}
		</fieldset>
EOR;
		return $result;
	}
}
?>