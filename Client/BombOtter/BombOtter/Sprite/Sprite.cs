﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;

namespace BombOtter.Sprite
{
    class Sprite
    {
        public Texture2D spriteTexture { get; set; }
        public int spriteWidth { get; set; }
        public int spriteHeight { get; set; }
        public Rectangle sourceRect { get; set; }
        public Vector2 spritePosition { get; set; }

        public Sprite(Texture2D texture, int width, int height)
        {
            spriteTexture = texture;
            spriteWidth = width;
            spriteHeight = height;
        }

        public Sprite(Texture2D texture, int width, int height, Vector2 position)
        {
            spriteTexture = texture;
            spriteWidth = width;
            spriteHeight = height;
            spritePosition = position;
        }
    }
}