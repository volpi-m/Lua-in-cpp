function main()
   local w = window.create("OUAIS")
   local evt = sfml.createEvent()
   local a = true
   local count = 0
   window.setFramerateLimit(w, 10)
   while window.isOpen(w) == 1 do
      while window.pollEvent(w, evt) do
         if sfml.isKeyPressed(keys.escape) or sfml.getEventType(evt) == event.Closed then
            window.close(w)
         end
      end
      window.clear(w, color.Blue)
      window.display(w)
   end
   window.destroy(w)
   sfml.destroyEvent(evt)
end
