//
// Created by user1 on 2017/06/23.
//

#include "featured_renderer.h"

static	int		ft_count_words(const char *str, char c)
{
    int	word;
    int	i;

    i = 0;
    word = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == c && str[i + 1] != c)
            word++;
        i++;
    }
    if (str[0] != '\0')
        word++;
    return (word);
}

static	char	*ft_word(const char *str, char c, int *i)
{
    char	*s;
    int		k;

    if (!(s = (char *)malloc(sizeof(s) * (strlen(str)))))
        return (NULL);
    k = 0;
    while (str[*i] != c && str[*i])
    {
        s[k] = str[*i];
        k++;
        *i += 1;
    }
    s[k] = '\0';
    while (str[*i] == c && str[*i])
        *i += 1;
    return (s);
}

char			**ft_strsplit(const char *str, char c)
{
    int		i;
    int		j;
    int		wrd;
    char	**s;

    i = 0;
    j = 0;
    wrd = ft_count_words(str, c);
    if (!(s = (char **)malloc(sizeof(s) * (wrd + 2))))
        return (NULL);
    while (str[i] == c && str[i])
        i++;
    while (j < wrd && str[i])
    {
        s[j] = ft_word(str, c, &i);
        j++;
    }
    s[j] = NULL;
    return (s);
}

int		countdirelements(std::string path, std::string file_type)
{
    int				o;
//    #ifdef WIN32

//    #else
    int				ft = (!strcmp(file_type.c_str(), "directories") ? 1 : (!strcmp(file_type.c_str(), "files") ? 2 : 0));//to use later
    DIR				*fd;
    struct	dirent	*dp;

    o = 0;
    if (!(fd = opendir("./")))
        return (0);
    while ((dp = readdir(fd)))
    {
//			if (file_type == 1)//then just count files not dirs.
        ++o;
        std::cout << dp->d_name << std::endl;
    }
    closedir(fd);
//#endif
    return (o);
}

char	**getdirelements(std::string path)
{
    int			    x;
    int				o;
    int				no_elements = countdirelements(path, "all");
    std::string		s;

//    #ifdef  _WIN32

//    #else
    DIR				*fd;
    struct	dirent	*dp;

    o = 0;
    x = -1;
    s = "";
    if (!no_elements || !(fd = opendir(path.c_str())))
        return (NULL);
    while ((dp = readdir(fd)) && ++o)
        if (dp->d_name && dp->d_name[0] != '.')
            s += static_cast<std::string>(dp->d_name) + "\n";
    closedir(fd);
//    #endif
    return (ft_strsplit(s.c_str(), '\n'));
}

featured_renderer::featured_renderer(void)
{

//    const  int          no_backgrounds = countdirelements("./textures/lib2/backgrounds/", "all"), no_food = countdirelements("./textures/lib2/food/", "all"), no_snake = countdirelements("./textures/lib2/snake/", "all"), no_snake_head = countdirelements("./textures/lib2/snake_head/", "all");
//
    this->background_movement_direction = -1;//zoom in z
//    this->backgrounds = getdirelements("./textures/lib2/backgrounds/");
//    this->snake_foods = getdirelements("./textures/lib2/food/");
//    this->snake_skins = getdirelements("./textures/lib2/snake/");
//    this->snake_heads = getdirelements("./textures/lib2/snake_head/");
    const  int             no_backgrounds = 4, no_food = 3, no_snake_head = 1, no_snake = 1;
    static std::string     backgrounds[no_backgrounds] = {"textures/lib2/backgrounds/Crab Nebula.bmp", "textures/lib2/backgrounds/algorithm.jpg", "textures/lib2/backgrounds/space.jpg", "textures/lib2/backgrounds/shrek.jpg"};
    static std::string     food[no_food] = {"textures/lib2/food/cabbage.bmp", "textures/lib2/food/onion.bmp", "textures/lib2/food/dead_rat.bmp"};
    static std::string     snakes[no_snake] = {"textures/lib2/snake/snake_body.bmp"};
    static std::string     snake_head[no_snake_head] = {"textures/lib2/snake_head/snake_skull.bmp"};

//    this->backgrounds = reinterpret_cast<char **>(backgrounds);//getdirelements("./textures/lib2/backgrounds/");
//    this->snake_foods = reinterpret_cast<char **>(food);//getdirelements("./textures/lib2/food/");
//    this->snake_skins = reinterpret_cast<char **>(snakes);//getdirelements("./textures/lib2/snake/");
//    this->snake_heads = reinterpret_cast<char **>(snake_head);

//    this->food = -1;
//    this->snake = -1;
    this->bodyswivel = 2;//to swivel in one direction
//    this->snake_head = -1;
//    this->background = -1;

    this->food = -1;
    this->snake = -1;
    this->background = -1;
    this->snake_head = -1;
    this->food_textures = new sf::Texture[no_food];
    this->snake_textures = new sf::Texture[no_snake];
    this->bg_textures = new sf::Texture[no_backgrounds];
    this->snake_head_textures = new sf::Texture[no_snake_head];
    this->window = new sf::RenderWindow(sf::VideoMode(640, 480), "Nibbler");
    this->window->setVerticalSyncEnabled(true);//testing
    while (++this->background < no_backgrounds)//this->backgrounds[++this->background])//++this->background < no_backgrounds)
        if (!this->bg_textures[this->background].loadFromFile(/* "./textures/lib2/backgrounds/" + */static_cast<std::string>(backgrounds[this->background]))) //|| !this->bg_textures[1].loadFromFile("../resources/algorithm.jpg") || !this->bg_textures[2].loadFromFile("../resources/space.jpg"))//, sf::IntRect(0, 0, 640, 480)))//if (!texture.loadFromFile("../Crab Nebula.bmp"))//also works
            featured_renderer::error_message("SFML texture Fails to load");
    while (++this->food < no_food)//this->snake_foods[++this->food])
        if (!this->food_textures[this->food].loadFromFile(/*"./textures/lib2/food/" +*/ static_cast<std::string>(food[this->food])))
            featured_renderer::error_message("SFML NO food texture");
    while (++this->snake_head < no_snake_head)//this->snake_heads[++this->snake_head])
        if (!this->snake_head_textures[this->snake_head].loadFromFile(/*"./textures/lib2/snake_head/" + */static_cast<std::string>(snake_head[this->snake_head])))//1
            featured_renderer::error_message("SFML NO snake skull texture");
    while (++this->snake < no_snake)//this->snake_skins[++this->snake])
        if (!this->snake_textures[this->snake].loadFromFile(/*"./textures/lib2/snake/" +*/ static_cast<std::string>(snakes[this->snake])))//2
            featured_renderer::error_message("SFML NO snake body texture");
    this->snake_head_textures->setSmooth(true);
    this->snake_textures->setSmooth(true);
    this->bg_textures->setSmooth(true);//enhances visuals of texture.

    this->background = rand() % no_backgrounds;//this->background;
    this->snake_head = rand() % no_snake_head;//this->snake_head;
    this->snake = rand() % no_snake;//this->snake;
    this->food = rand() % no_food;//this->food;

}

int     featured_renderer::error_message(std::string message)
{

    std::cout << message << std::endl;
    this->window->close();
    exit(EXIT_FAILURE);

    return (1);
}

featured_renderer::~featured_renderer(void)
{

//    int     y;
//
//    y = -1;
//    while (this->backgrounds[++y])
//        free(this->backgrounds[y]);
//    free(this->backgrounds);
//    y = -1;
//    while (this->snake_foods[++y])
//        free(this->snake_foods[y]);
//    free(this->snake_foods);
//    y = -1;
//    while (this->snake_skins[++y])
//        free(this->snake_skins[y]);
//    free(this->snake_skins);
//    y = -1;
//    while (this->snake_heads[++y])
//        free(this->snake_heads[y]);
//    free(this->snake_heads);
    delete [] this->food_textures;
    delete [] this->snake_textures;
    delete [] this->bg_textures;
    delete [] this->snake_head_textures;

    delete this->window;
   // delete [] this->bg_textures;

}

sf::RenderWindow    *&featured_renderer::getwindow(void)
{
    return (this->window);
}

void                featured_renderer::setwindow(sf::RenderWindow *window_data)
{
    this->window = window_data;
}

int                 featured_renderer::getbodyswivel(void)
{
    return (this->bodyswivel);
}

void                featured_renderer::setbodyswivel(int bs_data)
{
    this->bodyswivel = bs_data;
}

sf::Texture         *&featured_renderer::getbg_textures(void)
{
    return (this->bg_textures);
}

void                featured_renderer::setbg_textures(sf::Texture *bg_data)
{
    this->bg_textures = bg_data;
}

sf::Texture         *&featured_renderer::getsnake_textures(void)
{
    return (this->snake_textures);
}
void                featured_renderer::setsnake_textures(sf::Texture *s_data)
{
    this->snake_textures = s_data;
}

int                 featured_renderer::getbackground(void)
{
    return (this->background);
}

void                featured_renderer::setbackground(int bg_data)
{
    this->background = bg_data;
}

int                 featured_renderer::getsnake(void)
{
    return (this->snake);
}


void                featured_renderer::setsnake(int snake_data)
{
    this->snake = snake_data;
}

int                 featured_renderer::getfood(void)
{
    return (this->food);
}

void                featured_renderer::setfood(int food_data)
{
    this->food = food_data;
}

sf::Texture         *&featured_renderer::getsnake_head_textures(void)
{
    return (this->snake_head_textures);
}
void                featured_renderer::setsnake_head_textures(sf::Texture *sh_data)
{
    this->snake_head_textures = sh_data;
}

sf::Texture         *&featured_renderer::getfood_textures(void)
{
    return (this->food_textures);
}

void                featured_renderer::setfood_textures(sf::Texture *food_data)
{
    this->food_textures = food_data;
}

int                 featured_renderer::getsnake_head(void)
{
    return (this->snake_head);
}

void                featured_renderer::setsnake_head(int sh_data)
{
    this->snake_head = sh_data;
}

int                 featured_renderer::getbackground_movement_direction(void)
{
    return (this->background_movement_direction);
}

void                featured_renderer::setbackground_movement_direction(int direction)
{
    this->background_movement_direction = direction;
}
